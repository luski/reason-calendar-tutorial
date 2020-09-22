module DateFns = {
  type date = Js.Date.t;
  module Locale = {
    type t;
    [@bs.module "date-fns/locale/pl"] external pl: t = "default";
    [@bs.module "date-fns/locale/en-US"] external en: t = "default";
  };

  type formatOptions = {locale: Locale.t};
  type weekStartsOnOptions = {weekStartsOn: int};

  [@bs.module "date-fns"]
  external format: (date, string, formatOptions) => string = "format";
  [@bs.module "date-fns"] external addDays: (date, int) => date = "addDays";
  [@bs.module "date-fns"]
  external addMonths: (date, int) => date = "addMonths";
  [@bs.module "date-fns"]
  external startOfWeek: (date, weekStartsOnOptions) => date = "startOfWeek";
  [@bs.module "date-fns"] external startOfMonth: date => date = "startOfMonth";
  [@bs.module "date-fns"]
  external isSameDay: (date, date) => bool = "isSameDay";
};

type dayOfMonth = {
  number: int,
  isToday: bool,
  isForeign: bool,
};

let daysOfWeek = (locale, weekStartsOn) => {
  open DateFns;
  open Belt.Array;

  let days = [|0, 1, 2, 3, 4, 5, 6|];
  let firstDayOfWeek =
    startOfWeek(Js.Date.make(), {weekStartsOn: weekStartsOn});

  days->map(dayNumber =>
    firstDayOfWeek->addDays(dayNumber)->format("EE", {locale: locale})
  );
};

let createDateOfWeek = (monthNumber, date) => {
  number: Js.Date.getDate(date)->int_of_float,
  isToday: DateFns.isSameDay(date, Js.Date.make()),
  isForeign: Js.Date.getMonth(date) !== monthNumber,
};

let rec generateWeeks = (monthNum, startingDay, weeks) => {
  open Belt.Array;
  open DateFns;

  let week =
    [|0, 1, 2, 3, 4, 5, 6|]
    ->map(addDays(startingDay))
    ->map(createDateOfWeek(monthNum));

  if (!getUnsafe(week, 6).isForeign) {
    generateWeeks(
      monthNum,
      startingDay->addDays(7),
      concat(weeks, [|week|]),
    );
  } else {
    concat(weeks, [|week|]);
  };
};

let daysOfMonth = (date, weekStartsOn) => {
  open DateFns;

  let firstDayOfWeek =
    date->startOfMonth->startOfWeek({weekStartsOn: weekStartsOn});
  generateWeeks(Js.Date.getMonth(date), firstDayOfWeek, [||]);
};

[@react.component]
let make = (~locale=?, ~weekStartsOn=?) => {
  let localeValue = Belt.Option.getWithDefault(locale, DateFns.Locale.en);
  let weekStartsOnValue = Belt.Option.getWithDefault(weekStartsOn, 0);

  let (date, setDate) = React.useState(Js.Date.make);
  <div className="container font-lato p-2">
    <div className="flex items-center">
      <button
        onClick={_ => setDate(_ => DateFns.addMonths(date, -1))}
        className="text-white text-xl">
        {React.string({j|❮|j})}
      </button>
      <span
        className="flex-grow text-yellow font-bold text-center uppercase tracking-widest">
        {React.string(
           DateFns.format(date, "LLLL / yyyy", {locale: localeValue}),
         )}
      </span>
      <button
        onClick={_ => setDate(_ => DateFns.addMonths(date, 1))}
        className="text-white text-xl">
        {React.string({j|❯|j})}
      </button>
    </div>
    <table className="w-full capitalize">
      <thead>
        <tr>
          {daysOfWeek(localeValue, weekStartsOnValue)
           ->Belt.Array.map((day: string) =>
               <th key=day className="text-yellow font-bold h-20">
                 {React.string(day)}
               </th>
             )
           ->React.array}
        </tr>
        <tr> <td colSpan=7 className="h-2 bg-white" /> </tr>
      </thead>
      <tbody>
        {daysOfMonth(date, 1)
         ->Belt.Array.mapWithIndex((weekNumber, days) =>
             <tr key={string_of_int(weekNumber)} className="h-20 text-white ">
               {days
                ->Belt.Array.map(({number, isToday, isForeign}) =>
                    <td
                      key={string_of_int(number)}
                      className=Cn.(
                        "text-center"
                        + "text-yellow"->on(isToday)
                        + "text-gray-900"->on(isForeign)
                      )>
                      {number->string_of_int->React.string}
                    </td>
                  )
                ->React.array}
             </tr>
           )
         ->React.array}
        <tr> <td colSpan=7 className="h-2 bg-white" /> </tr>
      </tbody>
    </table>
  </div>;
};

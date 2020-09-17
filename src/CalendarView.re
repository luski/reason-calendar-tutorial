module DateFns = {
  type date = Js.Date.t;

  [@bs.module "date-fns"] external format: (date, string) => string = "format";
  [@bs.module "date-fns"] external addDays: (date, int) => date = "addDays";
  [@bs.module "date-fns"]
  external addMonths: (date, int) => date = "addMonths";
  [@bs.module "date-fns"] external startOfWeek: date => date = "startOfWeek";
  [@bs.module "date-fns"] external startOfMonth: date => date = "startOfMonth";
  [@bs.module "date-fns"] external isSameDay: (date, date) => bool = "isSameDay";
};

type dayOfMonth = {
  number: int,
  isToday: bool,
  isForeign: bool,
};

let daysOfWeek = () => {
  open DateFns;
  open Belt.Array;

  let days = [|0, 1, 2, 3, 4, 5, 6|];
  let firstDayOfWeek = startOfWeek(Js.Date.make());

  days->map(dayNumber =>
    firstDayOfWeek->addDays(dayNumber)->format(_, "EE")
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

let daysOfMonth = date => {
  open DateFns;

  let firstDayOfWeek = date->startOfMonth->startOfWeek;
  generateWeeks(Js.Date.getMonth(date), firstDayOfWeek, [||]);
};

[@react.component]
let make = () => {
  let (date, setDate) = React.useState(Js.Date.make);
  <div>
    <button onClick={_ => setDate(_ => DateFns.addMonths(date, -1))}>
      {React.string("<")}
    </button>
    <span> {React.string(DateFns.format(date, "MMMM / yyyy"))} </span>
    <button onClick={_ => setDate(_ => DateFns.addMonths(date, 1))}>
      {React.string(">")}
    </button>
    <table>
      <thead>
        <tr>
          {daysOfWeek()
           ->Belt.Array.map((day: string) =>
               <th key=day> {React.string(day)} </th>
             )
           ->React.array}
        </tr>
      </thead>
      <tbody>
        {daysOfMonth(date)
         ->Belt.Array.mapWithIndex((weekNumber, days) =>
             <tr key={string_of_int(weekNumber)}>
               {days
                ->Belt.Array.map(({number, isToday, isForeign}) =>
                    <td key={string_of_int(number)}>
                      {number->string_of_int->React.string}
                    </td>
                  )
                ->React.array}
             </tr>
           )
         ->React.array}
      </tbody>
    </table>
  </div>;
};

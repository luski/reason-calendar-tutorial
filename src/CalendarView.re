let daysOfWeek = () => MockData.daysOfWeek;
let daysOfMonth = () => MockData.daysOfMonth;

[@react.component]
let make = () => {
  <div>
    <button> {React.string("<")} </button>
    <span> {React.string("September / 2020")} </span>
    <button> {React.string(">")} </button>
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
        {daysOfMonth()
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

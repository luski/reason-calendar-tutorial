import React from "react";
import ReactDOM from "react-dom";
import { pl } from "date-fns/locale";

import { make as Calendar } from "./CalendarView.bs";

ReactDOM.render(
  <React.StrictMode>
    <div>
      <Calendar locale={pl} weekStartsOn={1} />
    </div>
  </React.StrictMode>,
  document.getElementById("root")
);

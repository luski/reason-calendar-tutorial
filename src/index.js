import React from "react";
import ReactDOM from "react-dom";
import { make as Calendar } from "./CalendarView.bs";

ReactDOM.render(
  <React.StrictMode>
    <div>
      <Calendar />
    </div>
  </React.StrictMode>,
  document.getElementById("root")
);

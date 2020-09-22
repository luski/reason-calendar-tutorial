import React from "react";
import ReactDOM from "react-dom";
import { pl } from "date-fns/locale";
import "./styles/style.css";

import { make as Calendar } from "./CalendarView.bs";

ReactDOM.render(
  <React.StrictMode>
    <div className="bg-gray-100 h-screen">
      <Calendar locale={pl} weekStartsOn={1} />
    </div>
  </React.StrictMode>,
  document.getElementById("root")
);

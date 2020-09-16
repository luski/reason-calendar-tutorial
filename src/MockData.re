type dayOfMonth = {
  number: int,
  isToday: bool,
  isForeign: bool,
};

let daysOfMonth = [|
  [|
    {number: 31, isToday: false, isForeign: true},
    {number: 1, isToday: false, isForeign: false},
    {number: 2, isToday: false, isForeign: false},
    {number: 3, isToday: false, isForeign: false},
    {number: 4, isToday: false, isForeign: false},
    {number: 5, isToday: false, isForeign: false},
    {number: 6, isToday: false, isForeign: false},
  |],
  [|
    {number: 7, isToday: false, isForeign: false},
    {number: 8, isToday: false, isForeign: false},
    {number: 9, isToday: false, isForeign: false},
    {number: 10, isToday: false, isForeign: false},
    {number: 11, isToday: true, isForeign: false},
    {number: 12, isToday: false, isForeign: false},
    {number: 13, isToday: false, isForeign: false},
  |],
  [|
    {number: 14, isToday: false, isForeign: false},
    {number: 15, isToday: false, isForeign: false},
    {number: 16, isToday: false, isForeign: false},
    {number: 17, isToday: false, isForeign: false},
    {number: 18, isToday: false, isForeign: false},
    {number: 19, isToday: false, isForeign: false},
    {number: 20, isToday: false, isForeign: false},
  |],
  [|
    {number: 21, isToday: false, isForeign: false},
    {number: 22, isToday: false, isForeign: false},
    {number: 23, isToday: false, isForeign: false},
    {number: 24, isToday: false, isForeign: false},
    {number: 25, isToday: false, isForeign: false},
    {number: 26, isToday: false, isForeign: false},
    {number: 27, isToday: false, isForeign: false},
  |],
  [|
    {number: 28, isToday: false, isForeign: false},
    {number: 29, isToday: false, isForeign: false},
    {number: 30, isToday: false, isForeign: false},
    {number: 31, isToday: false, isForeign: false},
    {number: 1, isToday: false, isForeign: true},
    {number: 2, isToday: false, isForeign: true},
    {number: 3, isToday: false, isForeign: true},
  |],
|];

let daysOfWeek = [|"sun", "mon", "tue", "wed", "thu", "fri", "sat"|];

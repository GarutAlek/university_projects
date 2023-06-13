% Copyright

implement main
    open core, stdio, file

class facts - footballDb
    команда : (integer TeamID, string TeamName, string TeamCity).
    стадион : (integer StadionID, string StadionName, string StadionCity).
    занимает : (integer Team1ID, integer Team2ID).
    футболист : (integer PlayerID, string PlayerName, integer PlayerAge, integer PlayerTeamID).
    роль : (string Role).

% работа_со_списками
class predicates
    длина_списка : (List*) -> integer N.
    сумма_списка : (integer* List) -> integer N.
    среднее : (integer* List) -> real N determ.
    максимальное : (integer* List, integer Max [out]) determ.
    минимальное : (integer* List, integer Min [out]) determ.

clauses
    длина_списка([]) = 0.
    длина_списка([_ | T]) = длина_списка(T) + 1.

    сумма_списка([]) = 0.
    сумма_списка([H | T]) = сумма_списка(T) + H.

    среднее(T) = сумма_списка(T) / длина_списка(T) :-
        длина_списка(T) > 0.

    максимальное([Max], Max).

    максимальное([H1, H2 | T], Max) :-
        H1 >= H2,
        максимальное([H1 | T], Max).

    минимальное([Min], Min).

    минимальное([H1, H2 | T], Min) :-
        H1 <= H2,
        минимальное([H1 | T], Min).

% генерация_и_вывод_списков
class predicates
    вывести_список : (integer*) determ.
    вывести_список : (string*) determ.
    вывести_список : (main::footballDb*) determ.
    список_команды : (integer TeamID) -> main::footballDb* TeamList determ.
    сумма_возрастов_команды : (integer TeamID) -> integer Sum.
    средний_возраст_игроков_команды : (integer TeamID) -> real Res determ.
    максимальный_возраст_игроков_команды : (integer TeamID) -> integer Res determ.
    минимальный_возраст_игроков_команды : (integer TeamID) -> integer Res determ.

clauses
    вывести_список([H | T]) :-
        write(H),
        nl,
        вывести_список(T).

    список_команды(TeamID) = TeamList :-
        TeamList = [ футболист(PlayerID, Name, Age, TeamID) || футболист(PlayerID, Name, Age, TeamID) ].

    сумма_возрастов_команды(ID) = Sum :-
        Sum = сумма_списка([ Age || футболист(_, _, Age, ID) ]).

    средний_возраст_игроков_команды(TeamID) = Res :-
        Res = среднее([ Age || футболист(_, _, Age, ID) ]).

    максимальный_возраст_игроков_команды(TeamID) = Max :-
        максимальное([ Age || футболист(_, _, Age, ID) ], Max),
        Res = Max.

    минимальный_возраст_игроков_команды(TeamID) = Min :-
        минимальное([ Age || футболист(_, _, Age, ID) ], Min),
        Res = Min.

% работа_с_программой
class predicates
    использовать_программу : () nondeterm.
    цифра_1 : (integer TeamID) determ.
    цифра_2 : (integer TeamID) determ.
    цифра_3 : (integer TeamID) determ.
    цифра_4 : (integer TeamID) determ.
    цифра_5 : (integer TeamID) determ.

clauses
    цифра_1(TeamID) :-
        Plist = список_команды(TeamID),
        write(Plist),
        nl,
        вывести_список(Plist),
        fail.
    цифра_1(TeamID) :-
        nl.

    цифра_2(TeamID) :-
        команда(TeamID, Name, _),
        write("Средний возраст игроков команды ", Name, " равен ", средний_возраст_игроков_команды(TeamID)),
        fail.
    цифра_2(TeamID) :-
        nl.

    цифра_3(TeamID) :-
        команда(TeamID, Name, _),
        write("Суммарный возраст игроков команды ", Name, " равен ", сумма_возрастов_команды(TeamID)),
        fail.
    цифра_3(TeamID) :-
        nl.

    цифра_4(TeamID) :-
        команда(TeamID, Name, _),
        write("Минимальный возраст игроков команды ", Name, " равен ", минимальный_возраст_игроков_команды(TeamID)),
        fail.
    цифра_4(TeamID) :-
        nl.

    цифра_5(TeamID) :-
        команда(TeamID, Name, _),
        write("Максимальный возраст игроков команды ", Name, " равен ", максимальный_возраст_игроков_команды(TeamID)),
        fail.
    цифра_5(TeamID) :-
        nl.

    использовать_программу() :-
        write("Добро пожаловать в справочный центр по футболу"),
        nl,
        write("Вот команды которые могут вам помочь узнать что нибудь про известные команды:"),
        nl,
        write("1 - вывести список игроков команды"),
        nl,
        write("2 - узнать средний возраст игроков команды"),
        nl,
        write("3 - узнать суммарный возраст игроков команды"),
        nl,
        write("4 - узнать минимальный возраст игроков команды"),
        nl,
        write("5 - узнать максимальный возраст игроков команды"),
        nl,
        write("Любая другая клавиша - завершить работу программы."),
        nl,
        Num = stdio::readLine(),
        if Num = "1" then
            write("Введите ID команды: "),
            nl,
            TTmp = stdio::readLine(),
            Tmp = toTerm(TTmp),
            if Tmp < 1 or Tmp > 20 then
                write("неподходящий ID"),
                nl,
                использовать_программу()
            else
                цифра_1(Tmp),
                использовать_программу()
            end if
        elseif Num = "2" then
            write("Введите ID команды: "),
            nl,
            TTmp = stdio::readLine(),
            Tmp = toTerm(TTmp),
            if Tmp < 1 or Tmp > 20 then
                write("неподходящий ID"),
                nl,
                использовать_программу()
            else
                цифра_2(Tmp),
                использовать_программу()
            end if
        elseif Num = "3" then
            write("Введите ID команды: "),
            nl,
            TTmp = stdio::readLine(),
            Tmp = toTerm(TTmp),
            if Tmp < 1 or Tmp > 20 then
                write("неподходящий ID"),
                nl,
                использовать_программу()
            else
                цифра_3(Tmp),
                использовать_программу()
            end if
        elseif Num = "4" then
            write("Введите ID команды: "),
            nl,
            TTmp = stdio::readLine(),
            Tmp = toTerm(TTmp),
            if Tmp < 1 or Tmp > 20 then
                write("неподходящий ID"),
                nl,
                использовать_программу()
            else
                цифра_4(Tmp),
                использовать_программу()
            end if
        elseif Num = "5" then
            write("Введите ID команды: "),
            nl,
            TTmp = stdio::readLine(),
            Tmp = toTerm(TTmp),
            if Tmp < 1 or Tmp > 20 then
                write("неподходящий ID"),
                nl,
                использовать_программу()
            else
                цифра_5(Tmp),
                использовать_программу()
            end if
        end if.

clauses
    run() :-
        file::consult("../consult.txt", footballDb),
        fail.
    run() :-
        использовать_программу(),
        fail.
    run() :-
        nl,
        nl,
        write("конец!").

end implement main

goal
    console::runUtf8(main::run).

Тестовое задание для компании Octavian Gaming.

Реализация Слот машины на языке C++. 
Выйгрышной ситуацией является совпадение не менее трех символов подряд в центральном ряде.
Для игры нажмите кнопку Start или пробел. Для ускорения - нажмите повторно.

В основе программы лежит паттерн state machine.
Для визуального отображения использована библиотека SFML 2.6.
Сборка производится с помощью CMake.

Краткое описание классов:
* Reel - Класс барабана, владеет конфигурацией символов (передается в конструктор), инкапсулирует текущее состояние барабана (скорость, текущее положение).
* State - Семейство классов инкапсулирующих поведение барабанов для каждой стадии игры.
* StateMachine - Управляет игрой: переключает стадии и связывает их состояние с интерфейсом (передает текущее время кадра и обрабатывает ивенты)
* UserInterface - Отображает текущее состояние колес и реагирует на ивенты (нажатия), рассчитывает время кадра.

Для сборки создайте папку build и пропишите в консоли:
cmake ..
cmake --build .
Для сборки под Linux необходимо изменить папку поиска библиотеки
# natUI
**Ключевые слова:** *native GUI, Windows, WinApi*

## Общая информация
**natUI** (*Native GUI*) - это библиотека обертка над WinApi предоставляющая возможность создавать графический пользовательский интерфейс в более удобном вариенте без лишнего кода по сравнению с WinApi. Однако, при этом возможности библиотеки ограничены по сравнению с WinApi, но упрощают создание и управление интерфейсом.

**natUI** предоставляет только нативный графический интерфейс ОС Windows и использует только WinApi.

**ВНИМАНИЕ!** Проект содержит мало/плохо/не тестированные места, которые будут дорабатываться в ходе использования библиотеки в других проектах.

### Немного истории
Изначально (примерно в 2016 году) эта библиотека планировалась как часть игрового движка SkyXEngine, однако теперь эта библиотека выделена в отдельный проект.

Этот проект пережил несколько реинкарнаций :)

### Дальнейшее равитие
Исходный код не является окончательным и будет улучшаться в мере необходимости. Новые функции, возможности, компоненты и прочие улучшения будут внедряться по ходу развития проекта.

## Использование
### Конфигурации сборки
Сборка проекта осуществлялась в Visual Studio, на данный момент только для 2013 версии. В планах сделать сборки и для других сред.
Сборки:
* Debug DLL - генерирует natui_dll_d.lib
* Debug Lib - генерирует natui_lib_d.lib
* Release DLL - генерирует natui_dll.lib
* Release Lib - генерирует natui_lib.lib

### Сборка
Каждый тип сборки имеет глобальное макроопределение:
* _NATUI_BUILD_DLL - для dll сборки
* _NATUI_BUILD_LIB - для lib сборки

### Подключение
Перед подключением заголовочного файла, необходимо сделать макроопределение в зависимости от использованной конфигурации сборки:
* _NATUI_USE_DLL - для использования dll (статическая линковка)
* _NATUI_USE_LIB - для использования lib

Для подключения библиотеки достаточно подключить заголовочный файл с интерфейсами:
	#include <natUI/natUI.h>

Или можно подключить natUI_wrap.h для того, чтобы использовать весь функционал библиотеки через пространство имен nui. Этот способ является предпочтительным, так как именование элементов кода сделано безотносительным и не включает в себя лишние символы ассоциирущие код с названием библиотеки. Например интерфейс окна представлен как IWindow, использование кода библиотеки без обертки в пространство имен, может вызывать конфиликты имен со сторонними файлами кода.

Для использования импорта из статической библиотеки либо при статической линковки dll необходимо подключить соответствующий конфигурации lib файл.

## Пример работы с интерфейсом
	//инициализация менеджера создания элементов
	IManager *pGUI = ManagerInit();
	
	//создания окна со стилем по умолчанию
	IWindow *pWnd = pWnd = pGUI->newWnd("Window", 10, 10, 300, 300, 0, WND_STYLE_DEFAULT);
	
	//установка видимости окну
	pWnd->setVisible(true);
	
	//создание кнопки в окне
	IButton *pButton = g_pGUI->newButton("button", 10, 10, 150, 30, pWnd);

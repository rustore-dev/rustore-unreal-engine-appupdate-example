### Unreal-плагин RuStore для обновления приложения

Плагин **RuStoreAppUpdateManager** помогает поддерживать актуальную версию вашего приложения на устройстве пользователя.
Поддерживаются версии Unreal Engine 5.3 и выше.

#### Установка плагина в свой проект

1. Перейдите в раздел [Релизы](https://gitflic.ru/project/rustore/rustore-unreal-engine-appupdate-example/release) репозитория проекта на GitFlic.

2. Скачайте из выбранного релиза артефакты:
   * `RuStoreAppUpdate.zip`
   * `RuStoreCore.zip`

3. Распакуйте скачанные архивы в папку `Plugins` в корне вашего Unreal-проекта, чтобы получилась следующая структура:

```
📁 your_project
└─ 📁 Plugins
   ├─ 📁 RuStoreAppUpdate
   │  ├─ 📁 Binaries
   │  ├─ 📁 Content
   │  ├─ 📁 Intermediate
   │  ├─ 📁 Resources
   │  ├─ 📁 Source
   │  └─ RuStoreAppUpdate.uplugin
   └─ 📁 RuStoreCore
      ├─ 📁 Binaries
      ├─ 📁 Content
      ├─ 📁 Intermediate
      ├─ 📁 Resources
      ├─ 📁 Source
      └─ RuStoreCore.uplugin
```

4. Перезапустите Unreal Engine.

5. В списке плагинов (**Edit → Plugins → Project → Mobile**) отметьте плагины **RuStoreAppUpdate** и **RuStoreCore**.

6. Подключите модули `RuStoreCore` и `RuStoreAppUpdate` в файле `YourProject.Build.cs` в списке `PublicDependencyModuleNames`.

7. В настройках проекта (**Edit → Project Settings → Android**) установите параметр **Minimum SDK Version** на уровень не ниже **24** и параметр **Target SDK Version** не ниже **31**.

#### Инициализация SDK

Перед вызовом методов библиотеки необходимо выполнить её инициализацию.

```cpp
URuStoreAppUpdateManager::Instance()->Init();
```

Все операции с менеджером также доступны из Blueprints.

Вызов `Init()` привязывает объект к корню сцены, и если дальнейшая работа с объектом больше не планируется, для освобождения памяти необходимо выполнить метод `Dispose()`. Вызов метода `Dispose` отвяжет объект от корня и безопасно завершит все отправленные запросы.

```cpp
URuStoreAppUpdateManager::Instance()->Dispose();
```

Если вам нужно проверить факт инициализации библиотеки, используйте метод `GetIsInitialized()`. Метод возвращает значение типа `bool`:

* `true` — если библиотека инициализирована;
* `false` — если `Init` еще не был вызван.

```cpp
bool bIsInitialized = URuStoreAppUpdateManager::Instance()->GetIsInitialized();
```

Подробнее об инициализации см. в <a href="https://www.rustore.ru/help/sdk/updates/unreal" target="_blank">руководстве онлайн</a>.

#### Работа с SDK

Начните изучение документации библиотеки RuStore с методов класса [URuStoreAppUpdateManager](@ref URuStoreAppUpdateManager). Или воспользуйтесь <a href="https://www.rustore.ru/help/sdk/updates/unreal" target="_blank">руководством онлайн</a>.

#### Техническая поддержка

Дополнительная помощь и инструкции доступны в <a href="https://www.rustore.ru/help" target="_blank">документации RuStore</a> и по электронной почте support@rustore.ru.

#### Условия распространения

Данное программное обеспечение, включая исходные коды, бинарные библиотеки и другие файлы, распространяется под лицензией MIT. Информация о лицензировании доступна в документе <a href="https://gitflic.ru/project/rustore/rustore-unreal-engine-appupdate-example/blob?file=MIT-LICENSE.txt" target="_blank">MIT-LICENSE</a>.
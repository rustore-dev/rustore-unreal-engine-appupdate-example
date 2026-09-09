<!-- ── Language switch (EN active) ──────────────────────────────────── -->
<div align="left" style="margin:0 0 14px 0;">

  <span style="display:inline-block;
               padding:.28rem .6rem;
               border:1px solid rgba(0,0,0,.18);
               border-radius:10px 0 0 10px;
               font-weight:400;
               font-size:12px;
               letter-spacing:.06em;
               color:#111827;
               background:linear-gradient(180deg,#ffffff,#f3f4f6);
               box-shadow:0 1px 0 rgba(0,0,0,.06);">
    [RU][ru]
  </span><span style="display:inline-block;
               margin-left:-1px;
               padding:.28rem .6rem;
               border:1px solid rgba(0,0,0,.14);
               border-radius:0 10px 10px 0;
               font-weight:400;
               font-size:12px;
               letter-spacing:.06em;
               color:#111827;
               background:linear-gradient(180deg,#e9edf2,#ffffff);
               box-shadow:inset 0 2px 6px rgba(0,0,0,.10);">
    EN
  </span>

</div>
<!-- ────────────────────────────────────────────────────────────────── -->

> ⚠️ Do not use the "Code → Download" button on the GitFlic website – this method does not download files from Git LFS. [Cloning instructions](README_CLONE.en.md).

## RuStore Unreal Engine plugin for app updates

### [🔗 Developer documentation][10]

The RuStoreAppUpdate plugin helps you keep your application up-to-date on the user's device.

The repository contains the "RuStoreAppUpdate" and "RuStoreCore" plugins, as well as a demo application with usage examples and settings. Versions UE 5.3 and above are supported.

### Installing the plugin in your project

1. Copy the contents of the `_Plugins_` folder into the `_Plugins_` folder inside your project. Restart Unreal Engine, and in the plugin list (Edit → Plugins → Project → Mobile), mark the "RuStoreAppUpdate" and "RuStoreCore" plugins.

2. In the `_YourProject.Build.cs_` file, under the `PublicDependencyModuleNames` list, add the modules "RuStoreCore" and "RuStoreAppUpdate".

3. In the project settings (Edit → Project Settings → Android), set the Minimum SDK Version to at least level 24 and the Target SDK Version to at least 31.

### Building the example application

You can explore the demo application that demonstrates all SDK methods:
- [README](unreal_example/README.en.md)
- [unreal_example](https://gitflic.ru/project/rustore/rustore-unreal-engine-appupdate-example/file?file=unreal_example)

### Rebuilding the plugin

If you need to modify the plugin libraries' code, you can make changes and rebuild the included .aar files.

1. Open the Android project from the `_unreal_plugin_libraries_` folder in your IDE.

2. Make the necessary changes.

3. Build the project using the gradle assemble command.

Upon successful build, updated files will be placed in:
- `_unreal_example / Plugins / RuStoreAppUpdate / Source / RuStoreAppUpdate / ThirdParty / Android / libs_`
- `_unreal_example / Plugins / RuStoreCore / Source / RuStoreCore / ThirdParty / Android / libs_`

These files include:
- RuStoreUnityAppUpdate.aar
- RuStoreUnityCore.aar

### Changelog

[CHANGELOG](CHANGELOG.en.md)

### Licensing Terms

This software, including source codes, binary libraries, and other files, is distributed under the MIT license. Licensing information is available in the [MIT-LICENSE](MIT-LICENSE.txt) document.

### Technical Support

Additional help and instructions are available at [rustore.ru/help/](https://www.rustore.ru/help/en/) or by email at [support@rustore.ru](mailto:support@rustore.ru).

[10]: https://www.rustore.ru/help/en/sdk/updates/unreal/10-5-1

[ru]: README.md
[en]: README.en.md

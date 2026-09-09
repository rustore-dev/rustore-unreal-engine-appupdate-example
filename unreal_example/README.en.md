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
               background:linear-gradient(180deg,#e9edf2,#ffffff);
               box-shadow:inset 0 2px 6px rgba(0,0,0,.10);">
    EN
  </span>

</div>
<!-- ────────────────────────────────────────────────────────────────── -->

## RuStore Unreal Engine plugin for app updates

### [🔗 Developer documentation][10]

- [SDK operating conditions](#SDK-operating-conditions)
- [Preparing required parameters](#Preparing-required-parameters)
- [Setting up the sample application](#Setting-up-the-sample-application)
- [Usage scenario](#Usage-scenario)
- [Distribution conditions](#Distribution-conditions)
- [Technical support](#Technical-support)


### SDK operating conditions

To use the RuStore In-app updates SDK, the following conditions must be met:

1. Android OS version 7.0 or higher.

2. RuStore is installed on the user's device.

3. The latest version of RuStore is installed on the user's device.

4. RuStore is allowed to install apps.


### Preparing required parameters

1. `applicationId` - a unique identifier of the application in the Android system in reverse domain name format (example: ru.rustore.sdk.example).

2. `*.keystore` - a key file used for [signing and authenticating Android applications](https://www.rustore.ru/help/en/developers/publishing-and-verifying-apps/app-publication/apk-signature/).


### Setting up the sample application

1. In project settings (Edit → Project Settings → Platforms → Android), specify the `applicationId` in the "Android Package Name" field — the app code from the RuStore developer console.

2. In project settings (Edit → Project Settings → Platforms → Android), under "Distribution Signing", specify the location and parameters of the previously prepared `*.keystore` file.

3. In project settings (Edit → Project Settings → Platforms → Android), in the "Store version" field, specify the app code. The value should be lower than the code of the published app in RuStore.

4. Build the project and test the app functionality.


### Usage scenario

#### Checking for updates

Tap the `Get AppUpdateInfo` button to perform the [check for available updates][20] procedure.

![Checking for updates](images/01_get_app_update_info.png)


#### Starting the update download

Tap the `Start update flow Delayed` button to initiate the [delayed update scenario][30] procedure.

![Starting the update download](images/02_start_update_flow_delayed.png)


#### Installing the update

Tap the `Complete update Silent` button to perform the [silent update completion][40] procedure.

![Installing the update](images/03_complete_update.png)


### Distribution conditions

This software, including source code, binary libraries, and other files, is distributed under the MIT license. Licensing information is available in the [MIT-LICENSE](MIT-LICENSE.txt) document.


### Technical support

Additional help and instructions are available on the page [rustore.ru/help/](https://www.rustore.ru/help/en/) and by email [support@rustore.ru](mailto:support@rustore.ru).

[10]: https://www.rustore.ru/help/en/sdk/updates/unreal/10-5-1
[20]: https://www.rustore.ru/help/en/sdk/updates/unreal/10-5-1#checkavailable
[30]: https://www.rustore.ru/help/en/sdk/updates/unreal/10-5-1#scenariodelayedupdate
[40]: https://www.rustore.ru/help/en/sdk/updates/unreal/10-5-1#installupdatesilent

[ru]: README.md
[en]: README.en.md

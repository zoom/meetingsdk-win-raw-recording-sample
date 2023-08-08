# Zoom Meeting SDK for Windows Raw Recording Sample

This sample uses the Zoom Meeting SDK for Windows in order to obtain recording permission and stream raw audio data.
This sample patches the existing "sdk_demo_v2" demo solution that can be downloaded with the Meeting SDK.

## Prerequisites

1. [vcpkg](https://vcpkg.io/en/)
1. [Zoom Account](https://support.zoom.us/hc/en-us/articles/207278726-Plan-Types-)
1. [Zoom Meeting SDK Credentials](#config:-sdk-credentials) (Instructions below)
    1. SDK Key
    1. SDK Secret

### Install Dependencies
Run the following in Powershell

```bash
# Use vcpkg to install dependencies
./vcpkg install yaml-cpp
./vcpkg install jwt-cpp
./vcpkg install boost
./vcpkg integrate install

```

### Clone the Repository

```bash
# Clone down this repository
git clone git@github.com:zoom/meetingsdk-win-raw-recording-sample.git
```

### Download the Zoom Windows SDK
Download the Zoom SDK for Windows version 5.14.5.15340 from the Zoom Marketplace and place it in the `meetingsdk-win-raw-recording-sample` folder that was just downloaded


### Apply The Patch

```bash
# Open the repository
cd meetingsdk-win-raw-recording-sample

git apply -p1 --directory zoom-sdk-windows-5.14.5.15340/x64 raw-recording-sample.patch
````

### Set Credentials

If you already have credentials from a Zoom Meeting SDK app then you can follow these steps to add them. Otherwise,
follow the section on how to [Create your Zoom Meeting SDK app](#create-your-zoom-meeting-sdk-app)

```bash
cd zoom-sdk-windows-5.14.5.15340/x64/demo/sdk_demo_v2

# Copy the config file and enter meeting details
cp sample.config.yaml config.yaml

# Copy the config file and enter Meeting SDK credentials (S2S Credentials are optional)
cp sample.credentials.yaml credentials.yaml
```

### Get your Zoom Meeting SDK Credentials

In your web browser, navigate to [Zoom Developer Portal](https://developers.zoom.us/) and register/log into your
developer account.

Click the "Build App" button at the top and choose to "Meeting SDK" application.

1. Name your app
2. Choose whether to list your app on the marketplace or not
3. Click "Create"
4. Fill out the prerequisite information
5. Copy the Client ID, Client Secret and Account ID to the credentials.yaml file

For more information, you can follow [this guide](https://developers.zoom.us/docs/meeting-sdk/developer-accounts/)

### (OPTIONAL) Get Your Server-to-Server Oauth Credentials

> If you want to use the Join Token method to join a meeting with recording permission then you'll need to provide Server-to-Server OAuth credentials and set the `join_token` option to `true` in config.yaml

In your web browser, navigate to [Zoom Developer Portal](https://developers.zoom.us/) and register/log into your
developer account.

Click the "Build App" button at the top and choose to "Server-to-Server OAuth" application.

1. Name your app
2. Choose whether to list your app on the marketplace or not
3. Click "Create"
4. Fill out the prerequisite information
5. Copy the Client ID, Client Secret and Account ID to the credentials.yaml file

For more information, you can follow [this guide](https://developers.zoom.us/docs/meeting-sdk/developer-accounts/)

### Configure Meeting

In config.yaml, enter the meeting details manually or provide a `join_url` to be parsed.

### Run the Solution

Now, open the x64/demo/sdk_demo_v2/sdk_demo_v2.sln solution file in Visual Studio. Run a Release x64 build per the
typical Windows Meeting SDK demo build. 

More information can be found [here](https://developers.zoom.us/docs/meeting-sdk/windows/get-started/build-run-play/)

### Keeping secrets secret

Remember, credentials should never be stored in a plaintext file for production use cases.

> :warning: **Never commit credentials.yaml to version control:** The file likely contains Zoom SDK and Zoom OAuth
> Credentials

### Testing

At this time there are no tests.

## Need help?

If you're looking for help, try [Developer Support](https://devsupport.zoom.us) or
our [Developer Forum](https://devforum.zoom.us). Priority support is also available
with [Premier Developer Support](https://zoom.us/docs/en-us/developer-support-plans.html) plans.

### Documentation

Make sure to review [our documentation]() as a reference when building your Zoom Apps.

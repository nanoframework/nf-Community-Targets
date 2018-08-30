image: Visual Studio 2017

build:
  verbosity: minimal

environment:
  GitHubUserName:
    secure: 7OBtVAMTodMWK20wg6pGnQ==
  GitHubUserEmail:
    secure: HeABB68Sn/Lhbd69C2cUcfWv0ab/rMDEcOLvcxf8gGw=
  GitHubToken:
    secure: WOqlCsnwTzfDPJFoNV/h8mEESIpG/9uFn1u6oE8hGZtXwIQQlsY+NyyLt9Y5xoFn

init:
  - git config --global core.autocrlf true
  - git config --global credential.helper store
  - ps: Add-Content "$env:USERPROFILE\.git-credentials" "https://$($env:GitHubToken):x-oauth-basic@github.com`n"
  - git config --global user.email "%GitHubUserEmail%"
  - git config --global user.name "%GitHubUserName%

install: 
  - ps: |

        git clone https://github.com/nanoframework/lib-CoreLibrary.git -b develop CoreLibrary --depth 1 -q

        git clone https://github.com/nanoframework/lib-nanoFramework.Runtime.Events.git -b develop nanoFramework.Runtime.Events --depth 1 -q

        git clone https://github.com/nanoframework/lib-nanoFramework.Runtime.Native.git -b develop nanoFramework.Runtime.Native --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Devices.Gpio.git -b develop Windows.Devices.Gpio --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Devices.I2c.git -b develop Windows.Devices.I2c --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Devices.Pwm.git -b develop Windows.Devices.Pwm --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Devices.SerialCommunication.git -b develop Windows.Devices.SerialCommunication --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Devices.Spi.git -b develop Windows.Devices.Spi --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Storage.Streams.git -b develop Windows.Storage.Streams --depth 1 -q

        git clone https://github.com/nanoframework/lib-Windows.Devices.Adc.git -b develop Windows.Devices.Adc --depth 1 -q

        git clone https://github.com/nanoframework/lib-nanoFramework.Hardware.Esp32 -b develop nanoFramework.Hardware.Esp32 --depth 1 -q

        git clone https://github.com/nanoframework/lib-nanoFramework.Networking.Sntp -b develop nanoFramework.Networking.Sntp --depth 1 -q

        git clone https://github.com/nanoframework/lib-nanoFramework.System.Net -b develop nanoFramework.System.Net --depth 1 -q

        .\install-vsix-appveyor.ps1

before_build:
  - ps: |
        git checkout $env:APPVEYOR_REPO_BRANCH -q
        choco install docfx -y
        # choco install nuget.commandline -y
      
        nuget sources add -name MyGet -Source https://www.myget.org/F/nanoframework-dev
      
        nuget restore CoreLibrary\source\nanoFramework.CoreLibrary.sln

        nuget restore nanoFramework.Runtime.Events\source\nanoFramework.Runtime.Events.sln

        nuget restore nanoFramework.Runtime.Native\source\nanoFramework.Runtime.Native.sln

        nuget restore Windows.Devices.Gpio\source\nanoFramework.Windows.Devices.Gpio.sln

        nuget restore Windows.Devices.I2c\source\nanoFramework.Windows.Devices.I2c.sln

        nuget restore Windows.Devices.Pwm\source\nanoFramework.Windows.Devices.Pwm.sln

        nuget restore Windows.Devices.SerialCommunication\source\nanoFramework.Windows.Devices.SerialCommunication.sln

        nuget restore Windows.Devices.Spi\source\nanoFramework.Windows.Devices.Spi.sln

        nuget restore Windows.Storage.Streams\source\nanoFramework.Windows.Storage.Streams.sln

        nuget restore Windows.Devices.Adc\source\nanoFramework.Windows.Devices.Adc.sln

        nuget restore nanoFramework.Hardware.Esp32\source\nanoFramework.Hardware.Esp32.sln

        nuget restore nanoFramework.Networking.Sntp\source\nanoFramework.Networking.Sntp.sln

        nuget restore nanoFramework.System.Net\source\nanoFramework.System.Net.sln

build_script:
  - ps: |
        msbuild CoreLibrary\source\nanoFramework.CoreLibrary.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild nanoFramework.Runtime.Events\source\nanoFramework.Runtime.Events.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild nanoFramework.Runtime.Native\source\nanoFramework.Runtime.Native.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Devices.Gpio\source\nanoFramework.Windows.Devices.Gpio.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Devices.I2c\source\nanoFramework.Windows.Devices.I2c.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Devices.Pwm\source\nanoFramework.Windows.Devices.Pwm.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Devices.SerialCommunication\source\nanoFramework.Windows.Devices.SerialCommunication.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Devices.Spi\source\nanoFramework.Windows.Devices.Spi.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Storage.Streams\source\nanoFramework.Windows.Storage.Streams.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild Windows.Devices.Adc\source\nanoFramework.Windows.Devices.Adc.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild nanoFramework.Hardware.Esp32\source\nanoFramework.Hardware.Esp32.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild nanoFramework.Networking.Sntp\source\nanoFramework.Networking.Sntp.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

        msbuild nanoFramework.System.Net\source\nanoFramework.System.Net.sln /p:Configuration=Release /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"

on_failure:
- ps: |

      cd ..

      .\appveyor-discord.ps1 failure $env:APPVEYOR_DISCORD_WEBHOOK_URL

after_build:
  - ps: >-

      .\rename-nfproj-files.ps1

      &docfx docfx.json
      
      if ($lastexitcode -ne 0)
      {
        throw [System.Exception] "docfx build failed with exit code $lastexitcode."
      }

      if(-Not $env:APPVEYOR_PULL_REQUEST_TITLE)
      {
        git clone https://github.com/nanoframework/nanoframework.github.io.git -b master origin_site -q
        Copy-Item _site/* origin_site -recurse -Force
        CD origin_site
        git add -A 2>&1
        git commit -m "CI Updates" -q
        git push origin master -q
      }

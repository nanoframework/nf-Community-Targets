[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![Discord](https://img.shields.io/discord/478725473862549535.svg)](https://discord.gg/gCyBu8T) [![Build Status](https://dev.azure.com/nanoframework/Community-Targets/_apis/build/status/nanoframework.nf-Community-Targets)](https://dev.azure.com/nanoframework/Community-Targets/_build/latest?definitionId=4)


![nanoFramework logo](https://github.com/nanoframework/Home/blob/master/resources/logo/nanoFramework-repo-logo.png)

-----

### Welcome to the **nanoFramework** community targets repository!

This repository contains target boards for the **nanoFramework**, provided and maintained by community members.

The provided boards are **NOT** supported by the **nanoFramework** team and any issues must be communicated with the contributor that _owns_ it.


## Available community boards


| Target name | Firmware Images | MCU | Frequency | FLASH | RAM |
|:-:|:-:|:-:|:-:|:-:|:-:|
| [GHI FEZ CERB40-I](CMSIS-OS/ChibiOS/GHI_FEZ_CERB40_NF) |  [ ![Download](https://api.bintray.com/packages/nfbot/nanoframework-images-community-targets/GHI_FEZ_CERB40_NF/images/download.svg) ](https://bintray.com/nfbot/nanoframework-images-community-targets/GHI_FEZ_CERB40_NF/_latestVersion)  | STM32F405RG | 168 MHz | 1024 KB | 192 KB |
| [IngenuityMicro Electron](CMSIS-OS/ChibiOS/I2M_ELECTRON_NF) | [ ![Download](https://api.bintray.com/packages/nfbot/nanoframework-images-community-targets/I2M_ELECTRON_NF/images/download.svg) ](https://bintray.com/nfbot/nanoframework-images-community-targets/I2M_ELECTRON_NF/_latestVersion) | STM32F411CE | 100 MHz | 512 KB | 128 KB |
| [IngenuityMicro Oxygen](CMSIS-OS/ChibiOS/I2M_OXYGEN_NF) | [ ![Download](https://api.bintray.com/packages/nfbot/nanoframework-images-community-targets/I2M_OXYGEN_NF/images/download.svg) ](https://bintray.com/nfbot/nanoframework-images-community-targets/I2M_OXYGEN_NF/_latestVersion) | STM32F411CE | 100 MHz | 512 KB | 128 KB |
| [ST Nucleo64 F401RE](CMSIS-OS/ChibiOS/ST_NUCLEO64_F401RE_NF) | [ ![Download](https://api.bintray.com/packages/nfbot/nanoframework-images-community-targets/ST_NUCLEO64_F401RE_NF/images/download.svg) ](https://bintray.com/nfbot/nanoframework-images-community-targets/ST_NUCLEO64_F401RE_NF/_latestVersion) | STM32F401RE | 84 MHz | 512 KB | 96 KB |
| [ST Nucleo64 F411RE](CMSIS-OS/ChibiOS/ST_NUCLEO64_F411RE_NF) | [ ![Download](https://api.bintray.com/packages/nfbot/nanoframework-images-community-targets/ST_NUCLEO64_F411RE_NF/images/download.svg) ](https://bintray.com/nfbot/nanoframework-images-community-targets/ST_NUCLEO64_F411RE_NF/_latestVersion) | STM32F411RE | 100 MHz | 512 KB | 128 KB |
| [ST Nucleo144 F412ZG](CMSIS-OS/ChibiOS/ST_NUCLEO144_F412ZG_NF) | [ ![Download](https://api.bintray.com/packages/nfbot/nanoframework-images-community-targets/ST_NUCLEO144_F412ZG_NF/images/download.svg) ](https://bintray.com/nfbot/nanoframework-images-community-targets/ST_NUCLEO144_F412ZG_NF/_latestVersion) | STM32F412ZG | 100 MHz | 1024 KB | 256 KB |


The above firmware builds include support for the class libraries and features marked below.


| Target | Gpio | Spi | I2c | Pwm | Adc | Serial | Events | SWO | Networking | Large Heap |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| GHI FEZ CERB40-I | :heavy_check_mark: | | :heavy_check_mark: | | | :heavy_check_mark: | :heavy_check_mark: | | | |
| IngenuityMicro Electron | :heavy_check_mark: | | | :heavy_check_mark: | | :heavy_check_mark: | | | | |
| IngenuityMicro Oxygen | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | | | |
| ST Nucleo64 F401RE | :heavy_check_mark: | | | | | | :heavy_check_mark: | :heavy_check_mark: | | |
| ST Nucleo64 F411RE | :heavy_check_mark: | | | | | | :heavy_check_mark: | :heavy_check_mark: | | |
| ST Nucleo144 F412ZG | :heavy_check_mark: | | :heavy_check_mark: | | | | :heavy_check_mark: | :heavy_check_mark: | | |

## Feedback and documentation

For documentation, providing feedback, issues and finding out how to contribute please refer to the [Home repo](https://github.com/nanoframework/Home).

When you need to discuss something specific about a community target start by doing so in the _support:community-targets_ channel in our Discord community or reach out directly to the target _owner_.

Join our Discord community [here](https://discord.gg/gCyBu8T).


## Credits

The list of contributors to this project can be found at [CONTRIBUTORS](https://github.com/nanoframework/Home/blob/master/CONTRIBUTORS.md).

The individual targets are _owned_ by the contributor and credit is due to the creator of the community board.


## License

The community target contributions are licensed under the [Apache 2.0 license](http://www.apache.org/licenses/LICENSE-2.0).


## Code of Conduct
This project has adopted the code of conduct defined by the [Contributor Covenant](http://contributor-covenant.org/)
to clarify expected behavior in our community.

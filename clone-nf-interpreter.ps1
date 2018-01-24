Write-Host "Downloading AlphaFS..."

$url = "https://github.com/alphaleonis/AlphaFS/releases/download/v2.1.3/AlphaFS.2.1.3.0.zip"
$output = "$PSScriptRoot\AlphaFS.zip"

# download zip with AlphaFS
(New-Object Net.WebClient).DownloadFile($url, $output)

Write-Host "Installing AlphaFS..."

# unzip
Expand-Archive $output -DestinationPath 'C:\mytools\AlphaFS'

Import-Module -Name 'C:\mytools\AlphaFS\Lib\Net452\AlphaFS.dll'

# copy CMSIS-OS community targets content to nf-interpreter community folder
[Alphaleonis.Win32.Filesystem.Directory]::Copy('C:\projects\nf-community-targets\CMSIS-OS\', 'C:\projects\nf-community-targets\nf-interpreter\targets-community\CMSIS-OS\')

Remove-Item -Path "$PSScriptRoot\AlphaFS.zip" -Force

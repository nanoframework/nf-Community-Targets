#build matrx with target names and build options
$BuildMatrix = ("GHI_FEZ_CERB40_NF", "-DTARGET_SERIES=STM32F4xx -DUSE_FPU=TRUE -DNF_FEATURE_DEBUGGER=TRUE -DSWO_OUTPUT=OFF -DNF_FEATURE_RTC=ON -DAPI_Windows.Devices.Gpio=ON -DAPI_Windows.Devices.Spi=ON -DAPI_Windows.Devices.I2c=ON -DAPI_Windows.Devices.Pwm=ON -DAPI_Windows.Devices.SerialCommunication=ON", 'True'),
("I2M_ELECTRON_NF", "-DTARGET_SERIES=STM32F4xx -DUSE_RNG=FALSE -DUSE_FPU=TRUE -DNF_FEATURE_DEBUGGER=TRUE -DSWO_OUTPUT=OFF -DNF_FEATURE_RTC=ON -DAPI_Windows.Devices.Gpio=ON -DAPI_Windows.Devices.Spi=ON -DAPI_Windows.Devices.I2c=ON -DAPI_Windows.Devices.Pwm=ON -DAPI_Windows.Devices.SerialCommunication=ON -DAPI_Windows.Devices.Adc=ON", 'True'),
("I2M_OXYGEN_NF", "-DTARGET_SERIES=STM32F4xx -DUSE_FPU=TRUE -DNF_FEATURE_DEBUGGER=TRUE -DSWO_OUTPUT=OFF -DNF_FEATURE_RTC=ON -DAPI_Windows.Devices.Gpio=ON -DAPI_Windows.Devices.Spi=ON -DAPI_Windows.Devices.I2c=ON -DAPI_Windows.Devices.Pwm=ON -DAPI_Windows.Devices.SerialCommunication=ON", 'True'),
("ST_NUCLEO64_F401RE_NF","-DTARGET_SERIES=STM32F4xx -DUSE_RNG=FALSE -DUSE_FPU=TRUE -DNF_FEATURE_DEBUGGER=TRUE -DSWO_OUTPUT=ON -DNF_FEATURE_RTC=ON -DAPI_Windows.Devices.Gpio=ON -DAPI_Windows.Devices.Spi=ON -DAPI_Windows.Devices.I2c=ON -DAPI_Windows.Devices.Pwm=ON -DAPI_Windows.Devices.SerialCommunication=ON -DAPI_Windows.Devices.Adc=ON", 'False')
("ST_NUCLEO64_F411RE_NF","-DTARGET_SERIES=STM32F4xx -DUSE_RNG=FALSE -DUSE_FPU=TRUE -DNF_FEATURE_DEBUGGER=TRUE -DSWO_OUTPUT=ON -DNF_FEATURE_RTC=ON -DAPI_Windows.Devices.Gpio=ON -DAPI_Windows.Devices.Spi=ON -DAPI_Windows.Devices.I2c=ON -DAPI_Windows.Devices.Pwm=ON -DAPI_Windows.Devices.SerialCommunication=ON", 'False')
 

# get commit message 
$commitMessage = "$env:APPVEYOR_REPO_COMMIT_MESSAGE" + " " + "$env:APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED"

# is there a target name in the commit message?
$targetCandidate = [regex]::Matches("$commitMessage",'[#]+\w+[#]').Value

if($targetCandidate -is [array])
{
    $global:BUILD_MATRIX = @(,@())

    ForEach($candidate in $targetCandidate)
    {
        # remove the leading and trailinig '#'
        $thisCandidate = $candidate -replace "#", ""

        # find if there is a target with this name
        ForEach($item in $BuildMatrix)
        {
            if(!$item[0].CompareTo($thisCandidate))
            {
                if($global:BUILD_MATRIX)
                {
                    $global:BUILD_MATRIX += , $item
                }
                else
                {
                    $global:BUILD_MATRIX = , $item
                }

                break;
            }
        }
    }
}
else
{
    if($targetCandidate)
    {
        # special case for #ALL# (build all targets)
        if(!$targetCandidate.CompareTo('#ALL#'))
        {
            # target to build is the board name
            $env:BOARD_NAME = "ALL"

            $global:BUILD_MATRIX = $BuildMatrix
        }
        else
        {
            # remove the leading and trailinig '#'
            $targetCandidate = $targetCandidate -replace "#", ""

            # find if there is a target with this name
            ForEach($item in $BuildMatrix)
            {
                if(!$item[0].CompareTo($targetCandidate))
                {
                    $env:BOARD_NAME = $item[0]
                    $env:BUILD_OPTIONS = $item[1]
                    $env:NEEDS_DFU = $item[2]
            
                    break;
                }
            }
        }
    }
    else
    {
        $env:BOARD_NAME = ''
    }
}

if($env:BOARD_NAME)
{
    if(!$env:BOARD_NAME.CompareTo('ALL'))
    {
        Write-Host "Build all targets"
    }
    else 
    {
        Write-Host "Target board is " $env:BOARD_NAME
    }
}
else 
{
    if($global:BUILD_MATRIX)
    {
        Write-Host "Build targets:"

        ForEach($item in $global:BUILD_MATRIX)
        {
            $env:BOARD_NAME += $item[0]+'|'
            Write-Host $item[0]
        }        
    }
    else
    {
        Write-Host "Nothing to build"
    } 
}


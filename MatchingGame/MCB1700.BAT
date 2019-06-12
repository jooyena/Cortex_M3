SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Java\jdk-12\bin;C:\Program Files\dotnet\;"C:\Users\ggb05\AppData\Local\Android\Sdk\tools;C:\Users\ggb05\AppData\Local\Android\Sdk\platform-tools;";C:\Program Files\Git\cmd;C:\Users\ggb05\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Bandizip\
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=MCB1700
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\startup_lpc17xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\system_lpc17xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\rtx_conf_cm.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\matchinggame.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\glcd.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc17xx_libcfg_default.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc17xx_pinsel.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc17xx_clkpwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc1768_utility.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc1768_fnd.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc17xx_timer.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc17xx_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\lpc17xx_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\MatchingGame.lnp"

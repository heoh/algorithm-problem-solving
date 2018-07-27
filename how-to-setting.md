개발환경: VSCode, MSVC2015 x64

저는 'VSCode > 파일(F) > 기본 설정(P) > 설정(S)' 에서 다음과 같이 설정하였습니다.

```
{
    "terminal.integrated.env.windows": {
        "PATH": "C:\\Program Files (x86)\\MSBuild\\14.0\\bin;${env:PATH}"
    },
    "C_Cpp.default.includePath": [
        "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\include",
        "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.10240.0\\ucrt"
    ],
    "C_Cpp.default.intelliSenseMode": "msvc-x64",
    "terminal.integrated.shell.windows": "C:\\Windows\\System32\\cmd.exe"
}
```
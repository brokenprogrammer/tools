# cob

COB is a tool that allows you to connect text strings to words. It can be a definition or something to help
you memorize something.

## Usage

```cmd
# Add a word explanation
cob MyWord "My Explanation"

# Get the explanation for an already added word
cob MyWord

# To update an already added explanation just follow the 
# instructions after trying to add an already existing word.
cob MyWord "My new updated explanation."
```

## Installation

COB uses Sqlite, most linux distros already comes with this pre-installed but on Windows you have to download
the following from [https://www.sqlite.org/download.html](https://www.sqlite.org/download.html).

* Source Code "sqlite-amalgamation-*.zip"
* Precompiled Binaries for Windows "sqlite-dll-win64-x64-*.zip"
* Precompiled Binaries for Windows "sqlite-tools-win32-x86-*.zip"

*NOTE*: Where the asterisk (*) is you have to have the same version for the downloaded libraries.

Exstract everything you've downloaded into a new folder in `C:/sqlite` and then you can run the build.bat script.
# <a name="top">ft_ssl_des</a>

ft_ssl is a program that recreates the functionalities of OpenSSL's base64, des-ecb, and des-cbc cipher commands. OpenSSL is a cryptographic toolkit library that is used to secure communications over computer networks.

## Contents

[Language & Functions Used](#language_functions) | [Installation](#install) | [Usage](#usage) | [Examples](#examples)

## <a name="language_functions">Language & Functions Used</a>

The ft_ssl program is written entirely in C, using only the following functions from the standard C libraries:

* open
* close
* read
* write
* getpass
* malloc
* free

<a href="#top">↥ back to top</a>

## <a name="install">Installation</a>

#### `Step 1` - clone the repo

```bash
$ git clone https://github.com/serena-zhu/ft_ssl_des.git
```

#### `Step 2` - compile program

```bash
$ make
```

The Makefile will compile a program named ft_ssl.

<a href="#top">↥ back to top</a>

## <a name="usage">Usage</a>

#### `General Usage`
```
$ ./ft_ssl
usage: ./ft_ssl command [command opts] [command args]
```
Running the program without any parameters will prompt the usage message.

#### `Supported Commands`
```
$ ./ft_ssl asdf
ft_ssl: Error: 'asdf' is an invalid command.

Standard commands:

Message Digest commmands:

Cipher commands:
base64
des
des-ecb
des-cbc
```
Passing an unsupported command will prompt the valid commands message. Note des is added as an alias for des-ecb. Standard and message digest commands along with more cipher commands will be added in future projects.

#### `Supported Options`
```
$ ./ft_ssl base64 asdf
unknown option 'asdf'
usage: enc -ciphername [-ade] [-base64] [-i file] [-v IV] [-k key] [-o file]

-a          Process base64 encoding/decoding (alias -base64)
-d          Decrypt the input data
-e          Encrypt the input data (default)
-i          Input file to read from (default stdin)
-k          Key to use, specified as a hexidecimal string
-o          Output file to write to (default stdout)
-v          IV to use, specified as a hexidecimal string

Valid cipher values:

-des
-des-cbc
-des-ecb
```

Passing invalid flags with commands will prompt the options message. Note some differences in the names of the options as compared to those in OpenSSL:

| ft_ssl | OpenSSL |
| :---: | :---: |
| -i | -in |
| -k | -K |
| -o | -out |
| -v | -iv |

<a href="#top">↥ back to top</a>

## <a name="examples">Examples</a>

#### `base64`
```bash
$ echo foobar | ./ft_ssl base64 -e
Zm9vYmFyCg==
$ echo Zm9vYmFyCg== | ./ft_ssl base64 -d | cat -e
foobar$
```

#### `des-ecb`
```bash
$ echo "your secret message" | ./ft_ssl des-ecb -e -a -k 8751B521C58F5416
f3slZBwuuNgd1YxLj7Wc5PErSP5NN8QZ
$echo f3slZBwuuNgd1YxLj7Wc5PErSP5NN8QZ | ./ft_ssl des -d -a -k 8751B521C58F5416 | cat -e
your secret message$
```

#### `des-cbc`
```bash
$ echo "your deep dark secret" | ./ft_ssl des-cbc -k 1E58B9952D147024 -v 987578ACDF577335 -o file.txt && cat -e file.txt
vQ^\M-j:M-0M-eM-=M-n>+M-YM-S3M-mM-;M-IoXM-j*M-[:^U
$ ./ft_ssl des-cbc -d -k 1E58B9952D147024 -v 987578ACDF577335 -i file.txt
your deep dark secret
```

<a href="#top">↥ back to top</a>

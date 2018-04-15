# ft_ssl_des

ft_ssl is a program that recreates the base64, des-ecb, and des-cbc cipher commands functionalities of OpenSSL. OpenSSL is a cryptographic toolkit library that is used to secure communications over computer networks.

## Contents

[Installation](#install) | [Usage](#usage) | [Examples](#examples)

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

## <a name="usage">Usage</a>

#### `General usage`
```
$ ./ft_ssl
usage: ./ft_ssl command [command opts] [command args]
```
Running the program name without any arguments will prompt the usage message.

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
Passing an unsupprted command will prompt the valid commands message. Note des is added as an alias for des-ecb. Standard and message digest commands along with more cipher commands will be added in future projects.

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

ft_ssl | OpenSSL
-i | -in
-k | -K
-o | -out
-v | -iv


Supported flags are: 

-a          Process base64 encoding/decoding (alias -base64)

-d          Decrypt the input data

-e          Encrypt the input data (default)

-i          Input file to read from (default stdin)

-k          Key to use, specified as a hexidecimal string

-o          Output file to write to (default stdout)

-v          IV to use, specified as a hexidecimal string
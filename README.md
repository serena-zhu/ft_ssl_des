# ft_ssl_des

ft_ssl is a program that recreates the base64, des-ecb, and des-cbc cipher commands functionalities of OpenSSL. OpenSSL is a cryptographic toolkit library that is used to secure communications over computer networks.

## Contents

[Installation](#install) | [Usage](#usage) | [Examples](#examples)

## <a name="install">Installation</a>

#### `Step 1` - clone the repo

```bash
$ git clone https://github.com/serena-zhu/ft_ssl_des.git
```

### `Step ` - compile program

```bash
$ make
```

## <a name="usage">Usage</a>

```
usage: ./ft_ssl command [command opts] [command args]
```

Supported flags are: 

-a          Process base64 encoding/decoding (alias -base64)

-d          Decrypt the input data

-e          Encrypt the input data (default)

-i          Input file to read from (default stdin)

-k          Key to use, specified as a hexidecimal string

-o          Output file to write to (default stdout)

-v          IV to use, specified as a hexidecimal string
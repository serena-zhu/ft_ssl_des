# ft_ssl_des
Recreate part of the OpenSSL functionality

Cipher commands supported are base64, des-ecb (alias ecb), and des-cbc.

usage: ./ft_ssl command [command opts] [command args]

Supported flags are: 

-a          Process base64 encoding/decoding (alias -base64)
-d          Decrypt the input data
-e          Encrypt the input data (default)
-i          Input file to read from (default stdin)
-k          Key to use, specified as a hexidecimal string
-o          Output file to write to (default stdout)
-v          IV to use, specified as a hexidecimal string

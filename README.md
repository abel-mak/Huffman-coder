make will generate binary huff
#### Test
###### encode
this command will generate encoded file example.huff.
```
$> ./huff -e example
```
```
$>ls -l
total 28
-rwxrwxrwx 1 user user   353 Sep 18 18:29 Makefile
-rwxrwxrwx 1 user user     0 Sep 18 19:11 README.md
-rwxrwxrwx 1 user user  1169 Sep 18 18:37 example
-rwxrwxrwx 1 user user   680 Sep 18 19:19 example.huff
-rwxrwxrwx 1 user user 18600 Sep 18 19:16 huff
drwxrwxrwx 1 user user  4096 Sep 18 19:16 src
```
###### decode
for decoding i will rename original file example to example1 because it will be overwritten
and then execute the command for decoding which will generate example.
```
$> mv example example1
$> ./huff -d example.huff
successfully decoded!👌
$> ls -l
-rwxrwxrwx 1 user user   353 Sep 18 18:29 Makefile
-rwxrwxrwx 1 user user     0 Sep 18 19:11 README.md
-rwxrwxrwx 1 user user  1169 Sep 18 19:27 example
-rwxrwxrwx 1 user user   680 Sep 18 19:26 example.huff
-rwxrwxrwx 1 user user  1169 Sep 18 19:23 example1
-rwxrwxrwx 1 user user 18600 Sep 18 19:16 huff
drwxrwxrwx 1 user user  4096 Sep 18 19:16 src
$> diff example example1
$> 
```

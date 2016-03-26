# 加法準同型暗号デモ(demo of additive homomorphic encryption)

# 動作環境
* x64 Windows + Visual Studio
* Linux + gcc, clang

# 動作方法

* ファイルを取得する。
```
md work
git clone git@github.com:herumi/xbyak.git
git clone git@github.com:herumi/cybozulib.git
git clone git@github.com:herumi/mcl.git
git clone git@github.com:herumi/add_he.git
git clone git@github.com:herumi/cybozulib_ext.git # only for Windows
```
* `add_he.cpp'をコンパイルする。
Windowsなら
```
cd add_he
mk.bat
```
Linuxなら
```
make
```

* 一度だけ秘密鍵と公開鍵を作成する。
```
./add_he.exe init
```
* サーバを起動する。
```
cd add_he
python server.py
```

* 確認
IE, Firefox, Chromeなどのブラウザで
`index.html`
を開く。

# License

modified new BSD License
http://opensource.org/licenses/BSD-3-Clause

# Author

MITSUNARI Shigeo(herumi@nifty.com)

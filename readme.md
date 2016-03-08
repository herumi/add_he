* ικ μµΚθΊΜηΏμιώ¶θΣχιο·εγ®ε¦¤

* ιλΚζ½ΨιΔ²κ¤ƒ
** x64 Windows + Visual Studio
** Linux + gcc, clang

* ιλΚζ½ΨθΜ»μµ•

** εγΚε¤£εβ¤εγ«εβΔη½φκΐΞε΅ωεβ¶ε€‚
```
md work
git clone git@github.com:herumi/xbyak.git
git clone git@github.com:herumi/cybozulib.git
git clone git@github.com:herumi/mcl.git
git clone git@github.com:herumi/sum_crypto.git
git clone git@github.com:herumi/cybozulib_ext.git # only for Windows
```
** `sum_crypto.cpp'εβΔε¤µεγ³εγΒε¤¦εγ«εαÒε£λεΰ‚
Windowsεαªεβ‰
```
cd sum_crypto
mk.bat
```
Linuxεαªεβ‰
```
make
```

** θΊ€κΌ¦εα εαΒι§Πη―¬λΊ·εα¨ιε¬ρφ¶λΊ·εβΔζ½Ψθ―πεαÒε£λεΰ‚
```
./sum_crypto.exe init
```
** εβµεγΌεγΐε£ςπ··ιλΚε΅ωεβ¶ε€‚
```
cd sum_crypto
python server.py
```

** ξ¤Ίπ¬
Firefox, Chromeεα®εα©εα΅εβ²ε΅λεα§
`index.html`
εβΔλΛλεαΎε€‚

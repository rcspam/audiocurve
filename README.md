# AudioCurve
![screenshot](https://cloud.githubusercontent.com/assets/7461595/8578640/1ba82028-25b0-11e5-93ad-dd8abd672e9e.png)
Convert your audio to curves in Natron.

# Install

```
git clone https://github.com/olear/audiocurve
cd audiocurve
qmake(-qt4|-qt5) && make
cp AudioCurve.* build/AudioCurve ~/.local/share/INRIA/Natron/Plugins/
yum install sox|apt-get install sox
```

# History

Based on the [audio2ascii](https://github.com/rcspam/audio2ascii) script by [@rcspam](https://github.com/rcspam), written from scratch in Qt for cross-platform support.

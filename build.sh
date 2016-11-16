mkdir '__targets_rel'
mkdir '__targets_rel/engine'
'g++' '-E' '-dM' '-x' 'c++' '/dev/null'
'g++' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=engine' '-o' '__targets_rel/engine/adsrscaler_test' 'engine/adsrscaler_test.cpp'
cat << 'MAIKE_CONFIG' > '__targets_rel/maikeconfig.json'
{
    "directoryoptions":{
        "paths_full_reject":[],
        "paths_reject":[
            "..",
            ".git",
            ".",
            "__targets_rel",
            "__targets"
        ],
        "recursive":1
    },
    "source_files":[
        "."
    ],
    "target_hooks":[
        {
            "config":{
                "appcompile":{
                    "args":[
                        "-O2",
                        "-fpic",
                        "{cxxversion}",
                        "-Wall",
                        "{cflags_extra}",
                        "{iquote}",
                        "{includedir}",
                        "-DMAIKE_TARGET_DIRECTORY={target_directory}",
                        "-DMAIKE_CURRENT_DIRECTORY={current_directory}",
                        "-o",
                        "{target}",
                        "{source}",
                        "{libdir}",
                        "{dependencies}"
                    ],
                    "name":"g++"
                },
                "cflags_extra":[
                    "march=native",
                    "-fast-math"
                ],
                "cflags_format":"-^",
                "cxxversion_max":-1,
                "cxxversion_min":201402,
                "dllcompile":{
                    "args":[
                        "-O2",
                        "-fpic",
                        "{cxxversion}",
                        "-Wall",
                        "{cflags_extra}",
                        "{iquote}",
                        "{includedir}",
                        "-DMAIKE_TARGET_DIRECTORY={target_directory}",
                        "-DMAIKE_CURRENT_DIRECTORY={current_directory}",
                        "-shared",
                        "-o",
                        "{target}",
                        "{source}",
                        "{libdir}",
                        "{dependencies}"
                    ],
                    "name":"g++"
                },
                "includedir":[],
                "includedir_format":"-I^",
                "includedir_noscan":[],
                "iquote":[
                    "."
                ],
                "iquote_format":"-iquote^",
                "libcompile":{
                    "args":[
                        "rcs",
                        "{target}",
                        "{dependencies}"
                    ],
                    "name":"ar"
                },
                "libdir":[],
                "libdir_format":"-L^",
                "libext_format":"-l^",
                "libint_format":"-l:^",
                "objcompile":{
                    "args":[
                        "-c",
                        "-O2",
                        "-fpic",
                        "{cxxversion}",
                        "-Wall",
                        "{cflags_extra}",
                        "{iquote}",
                        "{includedir}",
                        "-DMAIKE_TARGET_DIRECTORY={target_directory}",
                        "-DMAIKE_CURRENT_DIRECTORY={current_directory}",
                        "-o",
                        "{target}",
                        "{source}"
                    ],
                    "name":"g++"
                },
                "pkgconfig":{
                    "args":[
                        "{action}",
                        "{libname}"
                    ],
                    "name":"pkg-config"
                },
                "stdprefix":"-std=",
                "versionquery":{
                    "args":[
                        "-E",
                        "-dM",
                        "-x",
                        "c++",
                        "{nullfile}"
                    ],
                    "name":"g++"
                }
            },
            "filename_exts":[
                ".c++",
                ".cc",
                ".cpp",
                ".cxx",
                ".h",
                ".h++",
                ".hh",
                ".hpp",
                ".hxx"
            ],
            "name":"cxxdefault",
            "plugin":"targetcxx"
        },
        {
            "config":{
                "tohopper":{
                    "args":[
                        "{source}",
                        "{target_directory}"
                    ],
                    "name":"lv2spectohpp.php"
                },
                "tottler":{
                    "args":[
                        "{source}",
                        "{target_directory}"
                    ],
                    "name":"lv2spectottl.php"
                }
            },
            "filename_exts":[
                ".lv2spec"
            ],
            "name":"lv2specdefault",
            "plugin":"targetlv2spec"
        },
        {
            "config":{
                "command":{
                    "args":[
                        "--",
                        "{script}",
                        "{args}"
                    ],
                    "name":"python3"
                }
            },
            "filename_exts":[
                ".py"
            ],
            "name":"pythondefault",
            "plugin":"targetpython"
        }
    ],
    "targetinfo":{
        "architecture":"x86_64",
        "cpu_cache_alignment":64,
        "cpu_cache_flushsize":64,
        "cpu_cache_size":6144,
        "cpu_vendor":"GenuineIntel",
        "cpufeature_acpi":1,
        "cpufeature_aes":1,
        "cpufeature_aperfmperf":1,
        "cpufeature_apic":1,
        "cpufeature_arat":1,
        "cpufeature_arch_perfmon":1,
        "cpufeature_avx":1,
        "cpufeature_bts":1,
        "cpufeature_clflush":1,
        "cpufeature_cmov":1,
        "cpufeature_constant_tsc":1,
        "cpufeature_cx16":1,
        "cpufeature_cx8":1,
        "cpufeature_de":1,
        "cpufeature_ds_cpl":1,
        "cpufeature_dtes64":1,
        "cpufeature_dtherm":1,
        "cpufeature_dts":1,
        "cpufeature_eagerfpu":1,
        "cpufeature_epb":1,
        "cpufeature_ept":1,
        "cpufeature_erms":1,
        "cpufeature_est":1,
        "cpufeature_f16c":1,
        "cpufeature_flexpriority":1,
        "cpufeature_fpu":1,
        "cpufeature_fsgsbase":1,
        "cpufeature_fxsr":1,
        "cpufeature_ht":1,
        "cpufeature_ida":1,
        "cpufeature_lahf_lm":1,
        "cpufeature_lm":1,
        "cpufeature_mca":1,
        "cpufeature_mce":1,
        "cpufeature_mmx":1,
        "cpufeature_monitor":1,
        "cpufeature_msr":1,
        "cpufeature_mtrr":1,
        "cpufeature_nonstop_tsc":1,
        "cpufeature_nopl":1,
        "cpufeature_nx":1,
        "cpufeature_pae":1,
        "cpufeature_pat":1,
        "cpufeature_pbe":1,
        "cpufeature_pcid":1,
        "cpufeature_pclmulqdq":1,
        "cpufeature_pdcm":1,
        "cpufeature_pebs":1,
        "cpufeature_pge":1,
        "cpufeature_pln":1,
        "cpufeature_pni":1,
        "cpufeature_popcnt":1,
        "cpufeature_pse":1,
        "cpufeature_pse36":1,
        "cpufeature_pts":1,
        "cpufeature_rdrand":1,
        "cpufeature_rdtscp":1,
        "cpufeature_rep_good":1,
        "cpufeature_sep":1,
        "cpufeature_smep":1,
        "cpufeature_ss":1,
        "cpufeature_sse":1,
        "cpufeature_sse2":1,
        "cpufeature_sse4_1":1,
        "cpufeature_sse4_2":1,
        "cpufeature_ssse3":1,
        "cpufeature_syscall":1,
        "cpufeature_tm":1,
        "cpufeature_tm2":1,
        "cpufeature_tpr_shadow":1,
        "cpufeature_tsc":1,
        "cpufeature_tsc_deadline_timer":1,
        "cpufeature_vme":1,
        "cpufeature_vmx":1,
        "cpufeature_vnmi":1,
        "cpufeature_vpid":1,
        "cpufeature_xsave":1,
        "cpufeature_xsaveopt":1,
        "cpufeature_xtopology":1,
        "cpufeature_xtpr":1,
        "gnu":563048737669120,
        "gnu_string":"2.23",
        "linux":1125917086711808,
        "linux_string":"4.4.0-47-lowlatency",
        "nullfile":"/dev/null",
        "posix":200809,
        "target_directory":"__targets_rel",
        "wordsize":64,
        "x86_64":1
    }
}
MAIKE_CONFIG
'lv2spectottl.php' 'happychords.lv2spec' '__targets_rel'
'lv2spectohpp.php' 'happychords.lv2spec' '__targets_rel'
mkdir '__targets_rel/common'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=engine' '-o' '__targets_rel/engine/gatesequence.o' 'engine/gatesequence.cpp'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=engine' '-o' '__targets_rel/engine/gate.o' 'engine/gate.cpp'
'g++' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=engine' '-shared' '-o' '__targets_rel/happychords2.so' 'engine/pluginmain.cpp' '__targets_rel/engine/gate.o' '__targets_rel/engine/gatesequence.o' '-llv2plug'
mkdir '__targets_rel/ui'
'python3' '--' 'ui/background.py' '__targets_rel' 'ui'

Baking background image
'python3' '--' 'ui/knob.py' '__targets_rel' 'ui'
Baking knob sprites
'python3' '--' 'ui/knob.py' '__targets_rel' 'ui'
'python3' '--' 'ui/knob.py' '__targets_rel' 'ui'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-iquote.' '-I/usr/include/cairo' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/pixman-1' '-I/usr/include/freetype2' '-I/usr/include/libpng12' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets_rel/ui/imageresource.o' 'ui/imageresource.cpp'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets_rel/ui/knob.o' 'ui/knob.cpp'
'python3' '--' 'ui/switch.py' '__targets_rel' 'ui'
Baking switch sprites
'python3' '--' 'ui/switch.py' '__targets_rel' 'ui'
'python3' '--' 'ui/switch.py' '__targets_rel' 'ui'
'python3' '--' 'ui/switch.py' '__targets_rel' 'ui'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets_rel/ui/switch.o' 'ui/switch.cpp'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets_rel/ui/box.o' 'ui/box.cpp'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets_rel/ui/panel.o' 'ui/panel.cpp'
'g++' '-c' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets_rel/ui/stringchoice.o' 'ui/stringchoice.cpp'
'g++' '-O2' '-fpic' '-std=c++14' '-Wall' '-march=native' '--fast-math' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets_rel' '-DMAIKE_CURRENT_DIRECTORY=ui' '-shared' '-o' '__targets_rel/happychords2-gtk.so' 'ui/ui.cpp' '__targets_rel/ui/stringchoice.o' '__targets_rel/ui/panel.o' '__targets_rel/ui/box.o' '__targets_rel/ui/switch.o' '__targets_rel/ui/knob.o' '__targets_rel/ui/imageresource.o' '-lgtk-x11-2.0' '-lgdk-x11-2.0' '-lpangocairo-1.0' '-latk-1.0' '-lcairo' '-lgdk_pixbuf-2.0' '-lgio-2.0' '-lpangoft2-1.0' '-lpango-1.0' '-lgobject-2.0' '-lglib-2.0' '-lfontconfig' '-lfreetype' '-llv2plug_ui'
mkdir '__targets_rel/patterns'

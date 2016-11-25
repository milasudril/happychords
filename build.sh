mkdir '__targets/.kateproject.d'
mkdir '__targets/engine'
'g++' '-E' '-dM' '-x' 'c++' '/dev/null'
'g++' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=engine' '-o' '__targets/engine/adsrscaler_test' 'engine/adsrscaler_test.cpp'
'lv2spectottl.php' 'happychords.lv2spec' '__targets'
'lv2spectohpp.php' 'happychords.lv2spec' '__targets'
mkdir '__targets/ui'
cat << '+xk`BD+)I~>gu?*!4i+CBg<]9k~Q5C:{$nd/.P<W' > '__targets/maikeconfig.json'
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
                        "-g",
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
                "cflags_extra":[],
                "cflags_format":"-^",
                "cxxversion_max":-1,
                "cxxversion_min":201103,
                "dllcompile":{
                    "args":[
                        "-g",
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
                        "-g",
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
            "name":"targetcxx_default",
            "plugin":"targetcxx"
        },
        {
            "config":{
                "appcompile":{
                    "args":[
                        "-g",
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
                    "march=native"
                ],
                "cflags_format":"-^",
                "cxxversion_max":-1,
                "cxxversion_min":201402,
                "dllcompile":{
                    "args":[
                        "-g",
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
                        "-g",
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
            "name":"targetpython_default",
            "plugin":"targetpython"
        },
        {
            "config":{
                "tar":{
                    "command":{
                        "args":[
                            "{target_strip}",
                            "{root_append}",
                            "{compressor}",
                            "-cf",
                            "{target}",
                            "-T",
                            "-"
                        ],
                        "name":"tar"
                    },
                    "compressors":{
                        "bzip2":"-j",
                        "gzip":"-z",
                        "lzma":"-J"
                    },
                    "root_append":"--transform=s,\\\\(.*\\\\),^\\\\1,g",
                    "target_strip":"--transform=s,\\^^,,g"
                },
                "zip":{
                    "create":{
                        "args":[
                            "-@",
                            "{target}"
                        ],
                        "name":"zip"
                    },
                    "rename":{
                        "args":[
                            "-w",
                            "{target}"
                        ],
                        "name":"zipnote"
                    }
                }
            },
            "filename_exts":[
                ".archive"
            ],
            "name":"targetarchive_default",
            "plugin":"targetarchive"
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
        "project_root":"",
        "target_directory":"__targets",
        "wordsize":64,
        "x86_64":1
    }
}
+xk`BD+)I~>gu?*!4i+CBg<]9k~Q5C:{$nd/.P<W
'python3' '--' 'ui/background.py' '__targets' 'ui' '__targets/maikeconfig.json'
######################################################################
# Baking background image
mkdir '__targets/common'
'python3' '--' 'ui/knob.py' '__targets' 'ui' '__targets/maikeconfig.json'
# Baking knob sprites
# Blender:Read new prefs: /home/torbjorr/.config/blender/2.78/config/userpref.blend
# Blender:read blend: /home/torbjorr/Dokument/happychords/ui/knob.blend
# Blender: Circle
# Blender: bar
# Blender: Plane
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 3/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 903/4096
# Blender: Path Tracing Tile 4/4, Sample 904/4096
# Blender: Path Tracing Tile 4/4, Sample 905/4096
# Blender: Path Tracing Tile 4/4, Sample 910/4096
# Blender: Path Tracing Tile 4/4, Sample 1912/4096
# Blender: Path Tracing Tile 4/4, Sample 1914/4096
# Blender: Path Tracing Tile 4/4, Sample 1915/4096
# Blender: Path Tracing Tile 4/4, Sample 3023/4096
# Blender: Path Tracing Tile 4/4, Sample 3025/4096
# Blender: Path Tracing Tile 4/4, Sample 3030/4096
# Blender: Path Tracing Tile 4/4, Sample 3034/4096
# Blender: Path Tracing Tile 4/4, Sample 3600/4096
# Blender: Path Tracing Tile 4/4, Sample 3688/4096
# Blender: Path Tracing Tile 4/4, Sample 3919/4096
# Blender: Path Tracing Tile 4/4, Sample 3920/4096
# Blender: Path Tracing Tile 4/4, Sample 4093/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/knob_1.png'
# Blender: Time: 00:16.42 (Saving: 00:00.02)
# Blender:
# Blender: Circle.001
# Blender: bar
# Blender: Plane
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 3/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 113/4096
# Blender: Path Tracing Tile 4/4, Sample 114/4096
# Blender: Path Tracing Tile 4/4, Sample 116/4096
# Blender: Path Tracing Tile 4/4, Sample 123/4096
# Blender: Path Tracing Tile 4/4, Sample 911/4096
# Blender: Path Tracing Tile 4/4, Sample 914/4096
# Blender: Path Tracing Tile 4/4, Sample 916/4096
# Blender: Path Tracing Tile 4/4, Sample 925/4096
# Blender: Path Tracing Tile 4/4, Sample 1695/4096
# Blender: Path Tracing Tile 4/4, Sample 1698/4096
# Blender: Path Tracing Tile 4/4, Sample 1700/4096
# Blender: Path Tracing Tile 4/4, Sample 1705/4096
# Blender: Path Tracing Tile 4/4, Sample 2472/4096
# Blender: Path Tracing Tile 4/4, Sample 2478/4096
# Blender: Path Tracing Tile 4/4, Sample 2479/4096
# Blender: Path Tracing Tile 4/4, Sample 2485/4096
# Blender: Path Tracing Tile 4/4, Sample 3270/4096
# Blender: Path Tracing Tile 4/4, Sample 3276/4096
# Blender: Path Tracing Tile 4/4, Sample 3277/4096
# Blender: Path Tracing Tile 4/4, Sample 3283/4096
# Blender: Path Tracing Tile 4/4, Sample 3810/4096
# Blender: Path Tracing Tile 4/4, Sample 4000/4096
# Blender: Path Tracing Tile 4/4, Sample 4003/4096
# Blender: Path Tracing Tile 4/4, Sample 4008/4096
# Blender: Path Tracing Tile 4/4, Sample 4052/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/knob_2.png'
# Blender: Time: 00:21.40 (Saving: 00:00.00)
# Blender:
# Blender: Circle.001
# Blender: bar
# Blender: Plane
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 3/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 31/4096
# Blender: Path Tracing Tile 4/4, Sample 32/4096
# Blender: Path Tracing Tile 4/4, Sample 33/4096
# Blender: Path Tracing Tile 4/4, Sample 34/4096
# Blender: Path Tracing Tile 4/4, Sample 797/4096
# Blender: Path Tracing Tile 4/4, Sample 798/4096
# Blender: Path Tracing Tile 4/4, Sample 799/4096
# Blender: Path Tracing Tile 4/4, Sample 800/4096
# Blender: Path Tracing Tile 4/4, Sample 1563/4096
# Blender: Path Tracing Tile 4/4, Sample 1565/4096
# Blender: Path Tracing Tile 4/4, Sample 1566/4096
# Blender: Path Tracing Tile 4/4, Sample 1568/4096
# Blender: Path Tracing Tile 4/4, Sample 2327/4096
# Blender: Path Tracing Tile 4/4, Sample 2328/4096
# Blender: Path Tracing Tile 4/4, Sample 2330/4096
# Blender: Path Tracing Tile 4/4, Sample 2333/4096
# Blender: Path Tracing Tile 4/4, Sample 3092/4096
# Blender: Path Tracing Tile 4/4, Sample 3094/4096
# Blender: Path Tracing Tile 4/4, Sample 3095/4096
# Blender: Path Tracing Tile 4/4, Sample 3100/4096
# Blender: Path Tracing Tile 4/4, Sample 3783/4096
# Blender: Path Tracing Tile 4/4, Sample 3842/4096
# Blender: Path Tracing Tile 4/4, Sample 3843/4096
# Blender: Path Tracing Tile 4/4, Sample 3847/4096
# Blender: Path Tracing Tile 4/4, Sample 3989/4096
# Blender: Path Tracing Tile 4/4, Sample 4052/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/knob_3.png'
# Blender: Time: 00:21.71 (Saving: 00:00.00)
# Blender:
# Blender:addon not found: 'add_curve_sapling_3'
# Blender:Loading MHX2 importer-runtime v 0.27
# Blender:Loading MHX2 armature
# Blender:build loaded
# Blender:MHX2 armature loaded
# Blender:shaders.py
# Blender:shaders.py done
# Blender:MHX2 successfully (re)loaded
# Blender:addon not found: 'mesh_face_info_select'
# Blender:addon not found: 'simple_dev_tool_1_0_15'
# Blender:Loading makeclothes v 0.949
# Blender:Loading maketarget v 1.32
# Blender:MakeTarget loaded
# Blender:MakeClothes loaded
# Blender:Loading MakeWalk v 0.943
# Blender:MakeWalk loaded
# Blender:archimesh: added to phytonpath
# Blender:archimesh: Imported multifiles
# Blender:addon not found: 'mesh_extra_tools'
# Blender:version 3 imported
# Blender:
# Blender:Blender quit
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-iquote.' '-I/usr/include/cairo' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/pixman-1' '-I/usr/include/freetype2' '-I/usr/include/libpng12' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets/ui/imageresource.o' 'ui/imageresource.cpp'
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets/ui/knob.o' 'ui/knob.cpp'
'python3' '--' 'ui/switch.py' '__targets' 'ui' '__targets/maikeconfig.json'
# Baking switch sprite
# Blender:Read new prefs: /home/torbjorr/.config/blender/2.78/config/userpref.blend
# Blender:read blend: /home/torbjorr/Dokument/happychords/ui/switch.blend
# Blender: socket
# Blender: Switch
# Blender: bar
# Blender: Plane
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 64/4096
# Blender: Path Tracing Tile 4/4, Sample 69/4096
# Blender: Path Tracing Tile 4/4, Sample 70/4096
# Blender: Path Tracing Tile 4/4, Sample 72/4096
# Blender: Path Tracing Tile 4/4, Sample 1291/4096
# Blender: Path Tracing Tile 4/4, Sample 1292/4096
# Blender: Path Tracing Tile 4/4, Sample 1294/4096
# Blender: Path Tracing Tile 4/4, Sample 1297/4096
# Blender: Path Tracing Tile 4/4, Sample 2519/4096
# Blender: Path Tracing Tile 4/4, Sample 2520/4096
# Blender: Path Tracing Tile 4/4, Sample 2521/4096
# Blender: Path Tracing Tile 4/4, Sample 2526/4096
# Blender: Path Tracing Tile 4/4, Sample 3246/4096
# Blender: Path Tracing Tile 4/4, Sample 3319/4096
# Blender: Path Tracing Tile 4/4, Sample 3512/4096
# Blender: Path Tracing Tile 4/4, Sample 3513/4096
# Blender: Path Tracing Tile 4/4, Sample 3959/4096
# Blender: Path Tracing Tile 4/4, Sample 4022/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/switch_2.png'
# Blender: Time: 00:14.40 (Saving: 00:00.04)
# Blender:
# Blender: socket
# Blender: Switch
# Blender: bar
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 1649/4096
# Blender: Path Tracing Tile 4/4, Sample 1651/4096
# Blender: Path Tracing Tile 4/4, Sample 1657/4096
# Blender: Path Tracing Tile 4/4, Sample 1660/4096
# Blender: Path Tracing Tile 4/4, Sample 3017/4096
# Blender: Path Tracing Tile 4/4, Sample 3757/4096
# Blender: Path Tracing Tile 4/4, Sample 3759/4096
# Blender: Path Tracing Tile 4/4, Sample 3766/4096
# Blender: Path Tracing Tile 4/4, Sample 4071/4096
# Blender: Path Tracing Tile 4/4, Sample 4090/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/switch_3.png'
# Blender: Time: 00:07.21 (Saving: 00:00.00)
# Blender:
# Blender: socket
# Blender: Switch
# Blender: bar
# Blender: Plane
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 1/4
# Blender: Path Tracing Tile 3/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 1099/4096
# Blender: Path Tracing Tile 4/4, Sample 1100/4096
# Blender: Path Tracing Tile 4/4, Sample 1101/4096
# Blender: Path Tracing Tile 4/4, Sample 1102/4096
# Blender: Path Tracing Tile 4/4, Sample 2320/4096
# Blender: Path Tracing Tile 4/4, Sample 2321/4096
# Blender: Path Tracing Tile 4/4, Sample 2322/4096
# Blender: Path Tracing Tile 4/4, Sample 2323/4096
# Blender: Path Tracing Tile 4/4, Sample 3538/4096
# Blender: Path Tracing Tile 4/4, Sample 3539/4096
# Blender: Path Tracing Tile 4/4, Sample 3540/4096
# Blender: Path Tracing Tile 4/4, Sample 3541/4096
# Blender: Path Tracing Tile 4/4, Sample 3542/4096
# Blender: Path Tracing Tile 4/4, Sample 3663/4096
# Blender: Path Tracing Tile 4/4, Sample 4019/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/switch_4.png'
# Blender: Time: 00:14.02 (Saving: 00:00.00)
# Blender:
# Blender: socket
# Blender: Switch
# Blender: bar
# Blender: LookAt
# Blender: Camera
# Blender: Initializing
# Blender: Loading render kernels (may take a few minutes the first time)
# Blender: Waiting for render to start
# Blender: Updating Scene
# Blender: Updating Shaders
# Blender: Updating Background
# Blender: Updating Camera
# Blender: Updating Meshes Flags
# Blender: Updating Objects
# Blender: Copying Transformations to device
# Blender: Applying Static Transformations
# Blender: Updating Meshes
# Blender: Computing attributes
# Blender: Copying Attributes to device
# Blender: Building
# Blender: Building BVH
# Blender: Packing BVH triangles and strands
# Blender: Packing BVH nodes
# Blender: Copying BVH to device
# Blender: Computing normals
# Blender: Copying Mesh to device
# Blender: Updating Objects Flags
# Blender: Updating Images
# Blender: Updating Camera Volume
# Blender: Updating Hair Systems
# Blender: Copying Hair settings to device
# Blender: Updating Lookup Tables
# Blender: Updating Lights
# Blender: Computing distribution
# Blender: Updating Particle Systems
# Blender: Copying Particles to device
# Blender: Updating Integrator
# Blender: Updating Film
# Blender: Updating Lookup Tables
# Blender: Updating Baking
# Blender: Writing constant memory
# Blender: Path Tracing Tile 0/4
# Blender: Path Tracing Tile 4/4
# Blender: Path Tracing Tile 4/4, Sample 1510/4096
# Blender: Path Tracing Tile 4/4, Sample 1512/4096
# Blender: Path Tracing Tile 4/4, Sample 1513/4096
# Blender: Path Tracing Tile 4/4, Sample 1515/4096
# Blender: Path Tracing Tile 4/4, Sample 3733/4096
# Blender: Path Tracing Tile 4/4, Sample 3736/4096
# Blender: Path Tracing Tile 4/4, Sample 3738/4096
# Blender: Path Tracing Tile 4/4, Sample 3739/4096
# Blender: Path Tracing Tile 4/4, Sample 3791/4096
# Blender: Path Tracing Tile 4/4, Sample 3885/4096
# Blender: Path Tracing Tile 4/4, Sample 3952/4096
# Blender: Path Tracing Tile 4/4, Sample 4096/4096
# Blender: Finished
# Blender: Sce: Scene Ve:0 Fa:0 La:0
# Blender:Saved: '__targets/ui/switch_5.png'
# Blender: Time: 00:07.39 (Saving: 00:00.00)
# Blender:
# Blender:addon not found: 'add_curve_sapling_3'
# Blender:Loading MHX2 importer-runtime v 0.27
# Blender:Loading MHX2 armature
# Blender:build loaded
# Blender:MHX2 armature loaded
# Blender:shaders.py
# Blender:shaders.py done
# Blender:MHX2 successfully (re)loaded
# Blender:addon not found: 'mesh_face_info_select'
# Blender:addon not found: 'simple_dev_tool_1_0_15'
# Blender:Loading makeclothes v 0.949
# Blender:Loading maketarget v 1.32
# Blender:MakeTarget loaded
# Blender:MakeClothes loaded
# Blender:Loading MakeWalk v 0.943
# Blender:MakeWalk loaded
# Blender:archimesh: added to phytonpath
# Blender:archimesh: Imported multifiles
# Blender:addon not found: 'mesh_extra_tools'
# Blender:version 3 imported
# Blender:
# Blender:Blender quit
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets/ui/switch.o' 'ui/switch.cpp'
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets/ui/box.o' 'ui/box.cpp'
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets/ui/panel.o' 'ui/panel.cpp'
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-o' '__targets/ui/stringchoice.o' 'ui/stringchoice.cpp'
'g++' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-pthread' '-iquote.' '-I/usr/include/gtk-2.0' '-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include' '-I/usr/include/gio-unix-2.0/' '-I/usr/include/cairo' '-I/usr/include/pango-1.0' '-I/usr/include/atk-1.0' '-I/usr/include/pixman-1' '-I/usr/include/libpng12' '-I/usr/include/gdk-pixbuf-2.0' '-I/usr/include/harfbuzz' '-I/usr/include/glib-2.0' '-I/usr/lib/x86_64-linux-gnu/glib-2.0/include' '-I/usr/include/freetype2' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=ui' '-shared' '-o' '__targets/happychords-gtk.so' 'ui/ui.cpp' '__targets/ui/stringchoice.o' '__targets/ui/panel.o' '__targets/ui/box.o' '__targets/ui/switch.o' '__targets/ui/knob.o' '__targets/ui/imageresource.o' '-lgtk-x11-2.0' '-lgdk-x11-2.0' '-lpangocairo-1.0' '-latk-1.0' '-lcairo' '-lgdk_pixbuf-2.0' '-lgio-2.0' '-lpangoft2-1.0' '-lpango-1.0' '-lgobject-2.0' '-lglib-2.0' '-lfontconfig' '-lfreetype' '-llv2plug_ui'
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=engine' '-o' '__targets/engine/gatesequence.o' 'engine/gatesequence.cpp'
'g++' '-c' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=engine' '-o' '__targets/engine/gate.o' 'engine/gate.cpp'
'g++' '-g' '-fpic' '-std=c++14' '-Wall' '-march=native' '-iquote.' '-DMAIKE_TARGET_DIRECTORY=__targets' '-DMAIKE_CURRENT_DIRECTORY=engine' '-shared' '-o' '__targets/happychords.so' 'engine/pluginmain.cpp' '__targets/engine/gate.o' '__targets/engine/gatesequence.o' '-llv2plug'
'tar' '--transform=s,^__targets/,,g' '--transform=s,\(.*\),happychords.lv2/\1,g' '-z' '-cf' '__targets/happychords.tar.gz' '-T' '-' << '+xk`BD+)I~>gu?*!4i+CBg<]9k~Q5C:{$nd/.P<W'
LICENSE
__targets/manifest.ttl
ui/star.svg
ui/genpattern.m
__targets/maikeconfig.json
__targets/ui/background.png
__targets/plugindescriptor.hpp
__targets/happychords-gtk.so
patterns/gallop_backwards.txt
__targets/happychords.so

+xk`BD+)I~>gu?*!4i+CBg<]9k~Q5C:{$nd/.P<W
mkdir '__targets/patterns'

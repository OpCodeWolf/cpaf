{
  "targets": [
    {
      "target_name": "windowAPI",
      "sources": [
        "windowAPI.cpp" 
      ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include_dir\")",
        "<!@(pkg-config --cflags x11)",
        "../node_modules/node-addon-api",
      ],
      "libraries": [
        "<!@(pkg-config --libs x11)"
      ],
      "cflags!": [
      ],
      "cflags": [
        "-std=c++17"
      ],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ],
    }
  ]
}

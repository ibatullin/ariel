import qbs

CppApplication {
    name: "Ariel Test"
    Depends { name: "Ariel" }
    files: [
        "tst_ariel.cpp",
    ]
}

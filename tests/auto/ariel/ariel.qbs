import qbs

CppApplication {
    Depends { name: "Ariel" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.testlib" }

    name: "Ariel Test"
    type: ["application", "autotest"]
    files: [
        "tst_ariel.cpp",
    ]
}

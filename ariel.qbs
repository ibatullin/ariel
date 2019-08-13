import qbs

Project {
    name: "Ariel"
    minimumQbsVersion: "1.12.0"

    references: [
        "src/libs/ariel/ariel.qbs",
        "tests/tests.qbs"
    ]

    AutotestRunner { }
}

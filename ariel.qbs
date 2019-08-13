import qbs

Project {
    name: "Ariel"
    minimumQbsVersion: "1.12.0"

    references: [
        "src/ariel.qbs",
        "tests/tests.qbs",
        "examples/examples.qbs"
    ]

    AutotestRunner { }
}

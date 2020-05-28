import qbs
import qbs.FileInfo

StaticLibrary {
    name: "Ariel"

    Depends { name: "Qt.core" }
    Depends { name: "Qt.sql" }
    cpp.includePaths: [ product.sourceDirectory ]
    cpp.cxxLanguageVersion: "c++14"

    Export {
        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.sql" }
        cpp.includePaths: FileInfo.joinPaths(product.sourceDirectory, "../include")
    }

    files: [
        "attribute.cpp",
        "attribute.h",
        "bindvalue.cpp",
        "bindvalue.h",
        "collectors/abstractcollector.cpp",
        "collectors/abstractcollector.h",
        "collectors/sqlcollector.cpp",
        "collectors/sqlcollector.h",
        "comparisonoperator.cpp",
        "comparisonoperator.h",
        "comparisonoperator_p.h",
        "deletemanager.cpp",
        "deletemanager.h",
        "engine.cpp",
        "engine.h",
        "formatters/abstractvalueformatter.cpp",
        "formatters/abstractvalueformatter.h",
        "formatters/sqldriverformatter.cpp",
        "formatters/sqldriverformatter.h",
        "insertmanager.cpp",
        "insertmanager.h",
        "logicaloperator.cpp",
        "logicaloperator.h",
        "nodes/abstractnode.h",
        "nodes/attributenode.cpp",
        "nodes/attributenode.h",
        "nodes/binarynode.cpp",
        "nodes/binarynode.h",
        "nodes/bindvalue.cpp",
        "nodes/bindvalue.h",
        "nodes/comparisonoperators.h",
        "nodes/compoundoperators.h",
        "nodes/deletestatement.cpp",
        "nodes/deletestatement.h",
        "nodes/functions.cpp",
        "nodes/functions.h",
        "nodes/insertstatement.cpp",
        "nodes/insertstatement.h",
        "nodes/literalvalue.cpp",
        "nodes/literalvalue.h",
        "nodes/logicaloperators.cpp",
        "nodes/logicaloperators.h",
        "nodes/node.h",
        "nodes/order.cpp",
        "nodes/order.h",
        "nodes/selectcore.cpp",
        "nodes/selectcore.h",
        "nodes/selectstatement.cpp",
        "nodes/selectstatement.h",
        "nodes/tablenode.cpp",
        "nodes/tablenode.h",
        "nodes/unarynode.cpp",
        "nodes/unarynode.h",
        "nodes/updatestatement.cpp",
        "nodes/updatestatement.h",
        "selectmanager.cpp",
        "selectmanager.h",
        "table.cpp",
        "table.h",
        "table_p.h",
        "treemanager.cpp",
        "treemanager.h",
        "updatemanager.cpp",
        "updatemanager.h",
        "visitors/abstractvisitor.cpp",
        "visitors/abstractvisitor.h",
        "visitors/sqlitevisitor.h",
        "visitors/sqlvisitor.cpp",
        "visitors/sqlvisitor.h",
    ]
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 1280
    height: 720
    color: "#2e4147"
    title: qsTr("Hello World")

    QtObject {
        id: internal
        readonly property int rectWidth: 250
        readonly property int rectHeight: 50
        readonly property int rightMarginRect: 80
        readonly property int topMarginRect: 100
    }

    ColumnLayout {
        id: _udpPackageComponents
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.right: parent.right
        anchors.rightMargin: 60
        spacing: 5


        DataContainer {
            id: _ethernetFrameHeader
            width: 450
            componentDetail: udpInstance.ethernetFrameHeader
        }
        DataContainer {
            id: _ipv4Header
            componentDetail: ""
        }

        DataContainer {
            id: _ipHeaderChecksum
            componentDetail: ""
        }

        DataContainer {
            id: _sourceIPAdress
            componentDetail: ""
        }

        DataContainer {
            id: _destinationIPAdress
            componentDetail: ""
        }

        DataContainer {
            id: _udpHeader
            componentDetail: ""
        }

        DataContainer {
            id: _sourcePort
            componentDetail: ""
        }

        DataContainer {
            id: _destinationPort
            componentDetail: ""
        }

        DataContainer {
            id: _udpChecksum
            componentDetail: udpInstance.udpChecksum
        }

        DataContainer {
            id: _payload
            componentDetail: ""
        }
    }
}

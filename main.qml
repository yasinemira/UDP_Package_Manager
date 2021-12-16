import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 12150
    height: 720
    color: "#2e4147"
    title: qsTr("Hello World")

    QtObject {
        id: internal
        readonly property int rectWidth: 250
        readonly property int rectHeight: 50
        readonly property int rightMarginRect: 150
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
            width: 400
            componentDetail: udpInstance.ethernetFrameHeader
        }
        DataContainer {
            id: _ipv4Header            
            width: 280
            componentDetail: ""
        }

        DataContainer {
            id: _ipv4HeaderChecksum
            width: 150
            componentDetail: ""
        }

        DataContainer {
            id: _sourceIPAdress
            width: 150
            componentDetail: ""
        }

        DataContainer {
            id: _destinationIPAdress
            width: 150
            componentDetail: ""
        }

        DataContainer {
            id: _udpHeader
            width: 200
            componentDetail: ""
        }

        DataContainer {
            id: _sourcePort
            width: 150
            componentDetail: ""
        }

        DataContainer {
            id: _destinationPort
            width: 150
            componentDetail: ""
        }

        DataContainer {
            id: _udpChecksum
            width: 150
            componentDetail: udpInstance.udpChecksum
        }

        DataContainer {
            id: _payload
            componentDetail: ""
        }
    }
}

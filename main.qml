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
        readonly property int rightMarginRect: 150
        readonly property int topMarginRect: 100
    }

    ColumnLayout {
        id: _udpPackageComponents
        anchors.verticalCenter: parent.verticalCenter
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
            componentDetail: udpInstance.ipv4Header
        }

        DataContainer {
            id: _ipv4HeaderChecksum
            width: 150
            componentDetail: udpInstance.ipv4HeaderChecksum
        }

        DataContainer {
            id: _sourceIPAdress
            width: 150
            componentDetail: udpInstance.sourceIPAdress
        }

        DataContainer {
            id: _destinationIPAdress
            width: 150
            componentDetail: udpInstance.destinationIPAdress
        }

        DataContainer {
            id: _udpHeader
            width: 200
            componentDetail: udpInstance.udpHeader
        }

        DataContainer {
            id: _sourcePort
            width: 150
            componentDetail: udpInstance.sourcePort
        }

        DataContainer {
            id: _destinationPort
            width: 150
            componentDetail: udpInstance.destinationPort
        }

        DataContainer {
            id: _udpChecksum
            width: 150
            componentDetail: udpInstance.udpChecksum
        }

        DataContainer {
            id: _payload            
            width: 550
            componentDetail: udpInstance.payload
        }
    }
}

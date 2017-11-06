import QtQuick 2.9
import QtQuick.Controls 2.2
import CustomGeometry 1.0


import "../Nodes"
import "../Nodes/Operator"
import "../Nodes/Operator/BinaryOperator"
import "../Nodes/Operator/BinaryOperator/Logical"
import "../Nodes/Operator/UnaryOperator"

DulyCanvas {
    id: canvas
    property int margin: 30
    gridStep: 15
    gridColor: toolBar.menuEditRef.settingRef.themeTabRef.gridColorRef.colorSetting
    accentGridStep: 150
    accentGridColor: toolBar.menuEditRef.settingRef.themeTabRef.accentGridColorRef.colorSetting
    backgroundColor: toolBar.menuEditRef.settingRef.themeTabRef.backgroudColorRef.colorSetting

    Node {
        model: AddNodeModel{}
    }
    Node {
        y: 200
        model: AddNodeModel{}
    }

    Rectangle {
        x: parent.width / 2
        y: parent.height / 2
        width: 5
        height: 5
    }

    Label {
        id: zoomText
        text: (canvas.scaleFactor * 100) + "%"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }
    onScaleFactorChanged: {
        zoomText.text = Math.round(canvas.scaleFactor * 100) + "%"
    }
}

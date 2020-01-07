import QtQuick 2.0
import QtQuick.Controls 2.0
import SkiaQuickItem 1.0
Rectangle {
    width: 800
    height: 600
    color: "lightgray"
    SkiaQuickItem {
        width: 400
        height: 300
        anchors.centerIn: parent
    }
}

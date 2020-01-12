import QtQuick 2.0
import QtQuick.Controls 2.0
import SkiaQuickItem 1.0
Rectangle {
    width: 800
    height: 600
    color: "lightgray"
    SkiaQuickItem {
        id: t
        width: 600
        height: 400
        anchors.centerIn: parent
        RotationAnimation {
            target: t
            running: true
            from: 0; to: 360; duration: 2000; loops: -1
        }
    }
}

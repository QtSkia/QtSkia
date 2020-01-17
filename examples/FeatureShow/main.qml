import QtQuick 2.0
import QtQuick.Controls 2.0
import SkiaItem 1.0
Rectangle {
    width: 800
    height: 600
    color: "lightgray"
    SwipeView {
        id: view
        currentIndex: 0
        width: 600
        height: 400
        anchors.centerIn: parent
        clip: true
        SkiaShapeItem{}
        SkiaBezierItem {}
        SkiaRotationItem {}
        SkiaTextItem {}
        SkiaDiscreteItem {}
        SkiaComposeItem {}
        SkiaSumPathItem {}
        SkiaShaderItem {}
    }
    PageIndicator {
        id: indicator
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        delegate: Rectangle {
            implicitWidth: 16
            implicitHeight: implicitWidth
            radius: width / 2
            color: index===indicator.currentIndex ? "gray" : Qt.lighter("gray")
            Text {
                anchors.centerIn: parent
                text: index
                color: "red"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.setCurrentIndex(index)
                }
            }
        }
    }
}

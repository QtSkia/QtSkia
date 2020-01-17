import QtQuick 2.0
import QtQuick.Controls 2.0
import SkiaLottieItem 1.0
Rectangle {
    width: 800
    height: 600
    color: "lightgray"
    SkiaLottieItem {
        anchors.centerIn: parent
        width: 400
        height: 300
        source: resPath + "/techno_penguin.json"
        Component.onCompleted: {
            start();
        }
    }
}

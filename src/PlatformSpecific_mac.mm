#include <QGuiApplication>
#include <QPalette>
#include <QColor>
#import <AppKit/AppKit.h>

namespace {

QColor qt_mac_toQColor(const NSColor *color)
{
    QColor qtColor;
    NSString *colorSpace = [color colorSpaceName];
    if (colorSpace == NSDeviceCMYKColorSpace) {
        CGFloat cyan, magenta, yellow, black, alpha;
        [color getCyan:&cyan magenta:&magenta yellow:&yellow black:&black alpha:&alpha];
        qtColor.setCmykF(cyan, magenta, yellow, black, alpha);
    } else {
        NSColor *tmpColor;
        tmpColor = [color colorUsingColorSpaceName:NSDeviceRGBColorSpace];
        CGFloat red, green, blue, alpha;
        [tmpColor getRed:&red green:&green blue:&blue alpha:&alpha];
        qtColor.setRgbF(red, green, blue, alpha);
    }
    return qtColor;
}

} // namespace


void mac_patchPlaceholderColor() {
	// TODO: this only patches on start-up. If macOS switches to dark mode while
	// the application is running, the palette is not fixed. I'm not sure
	// `QGuiApplication::paletteChanged` is emitted when this happens, but if it
	// is, it will be tricky to differentiate between the paletteChanged caused
	// by the host OS or by us patching the palette.
	QPalette palette = QGuiApplication::palette();
	palette.setColor(QPalette::PlaceholderText, qt_mac_toQColor([NSColor placeholderTextColor]));
	QGuiApplication::setPalette(palette);
}

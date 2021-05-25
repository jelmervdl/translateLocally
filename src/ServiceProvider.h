#ifndef SERVICEPROVIDER_H
#define SERVICEPROVIDER_H

#include <QObject>

/**
 * ServiceProvider:
 * C++ class that signals translation requests when the application is called
 * through macOS's Services menu. QObject so it can emit signals.
 * 
 * ServiceProviderImpl: 
 * Objective-C class that hooks into NSApplication to work as servicesProvider.
 * This will call back to the ServiceProvider which will then emit the signal
 * that's accessable in the rest of the application.
 * 
 * ServiceProviderRef:
 * When compiled as C++, void pointer. When compiled as Obj-C, pointer to
 * ServiceProviderImpl. Since ServiceProvider.mm is compiled as Obj-C, it should
 * be properly checked. Assuming both pointer types the same size.
 */

#ifdef __OBJC__
#import <CoreFoundation/CoreFoundation.h>
#import <AppKit/AppKit.h>
#else
#include <objc/objc.h>
#endif

#ifdef __OBJC__

class ServiceProvider;

@interface ServiceProviderImpl : NSObject
{
	ServiceProvider *parent_;
}

- (ServiceProviderImpl *)initWithParent: (ServiceProvider *)parent;
- (void)translate:(NSPasteboard *)pboard
         userData:(NSString *)userData
            error:(NSString **)error;
@end

typedef ServiceProviderImpl* ServiceProviderRef;

#else

typedef id ServiceProviderRef;

#endif

class ServiceProvider : public QObject {
	Q_OBJECT
private:
	ServiceProviderRef impl_;

public:
	ServiceProvider(QObject *parent = nullptr);
	~ServiceProvider();
	void requestTranslation(QString input);

signals:
	void translationRequested(QString input);
};

#endif

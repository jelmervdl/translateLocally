#ifndef SERVICEPROVIDER_H
#define SERVICEPROVIDER_H

#include <QObject>

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

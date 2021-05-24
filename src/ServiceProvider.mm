#include "ServiceProvider.h"

#include <QObject>

@implementation ServiceProviderImpl

- (ServiceProviderImpl *)initWithParent: (ServiceProvider *)parent {
	[self init];
	parent_ = parent;
	return self;
}

- (void)translate:(NSPasteboard *)pboard
				 userData:(NSString *)userData
						error:(NSString **)error {
	NSLog(@"translate triggered");

	// Test for strings on the pasteboard.
	NSArray *classes = [NSArray arrayWithObject:[NSString class]];
	NSDictionary *options = [NSDictionary dictionary];

	if (![pboard canReadObjectForClasses:classes options:options]) {
		*error = NSLocalizedString(@"Error: couldn't encrypt text.",
				 @"pboard couldn't give string.");
		return;
	}

	// Get and encrypt the string.
	NSString *pboardString = [pboard stringForType:NSPasteboardTypeString];
	parent_->requestTranslation([pboardString UTF8String]);

	// Write the encrypted string onto the pasteboard.
	// [pboard clearContents];
	// [pboard writeObjects:[NSArray arrayWithObject:newString]];
}

@end

ServiceProvider::ServiceProvider(QObject *parent)
: QObject(parent) {
	impl_ = [[ServiceProviderImpl alloc] initWithParent: this];
	NSApplication *app = [NSApplication sharedApplication];
	[app setServicesProvider: impl_];
}

ServiceProvider::~ServiceProvider() {
	NSApplication *app = [NSApplication sharedApplication];
	[app setServicesProvider: nil];
	[impl_ dealloc];
}

void ServiceProvider::requestTranslation(QString input) {
	emit translationRequested(input);
}

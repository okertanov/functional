//
//  NQCWindow.h
//
//  Created by Nata Kertanova on 11/16/10.
//  Copyright 2010 SIA SS. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NQCWindow : NSWindow 
{
	NSRect origWinFrame;
	NSUInteger origStyleMask;
	bool isFullScreen;
}

- (id)   initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle 
					 backing:(NSBackingStoreType)bufferingType 
					 defer:(BOOL)flag;
- (BOOL) canBecomeKeyWindow;
- (BOOL) canBecomeMainWindow;

- (void) toggleFullScreen;

@end

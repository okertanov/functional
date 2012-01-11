//
//  NQCWindow.m
//
//  Created by Nata Kertanova on 11/16/10.
//  Copyright 2010 SIA SS. All rights reserved.
//

#import "NQCWindow.h"
#import <Quartz/Quartz.h>
#import <Carbon/Carbon.h>

@implementation NQCWindow

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle 
				  backing:(NSBackingStoreType)bufferingType 
				  defer:(BOOL)flag
{
	isFullScreen = false;
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    return self;
}

-(BOOL) canBecomeKeyWindow
{
	NSLog( @"Inside canBecomeKeyWindow" );
	return true;
}


-(BOOL) canBecomeMainWindow
{
	NSLog( @"Inside canBecomeMainWindow" );
	return true;
}

-(void)toggleFullScreen
{
	//NSRunAlertPanel(@"Debug Alert", @"Here is...", @"OK", nil, nil);
	if ( true == (isFullScreen = !isFullScreen) )
	{
		NSLog( @"Entering full screen mode. %p", self );
		origWinFrame = [self frame];
		origStyleMask = [self styleMask];
		SetSystemUIMode(kUIModeAllHidden, kUIOptionAutoShowMenuBar);
		//[window performZoom:sender];
		[self setStyleMask: NSBorderlessWindowMask];
		[self setFrame:[[NSScreen mainScreen] frame] display:YES animate:NO];
	}
	else 
	{		
		NSLog( @"Leaving full screen mode. %p", self );
		SetSystemUIMode(kUIModeNormal, kUIOptionAutoShowMenuBar);
		[self setStyleMask: origStyleMask];
		[self setFrame:origWinFrame display:YES animate:NO];
	}
}

@end

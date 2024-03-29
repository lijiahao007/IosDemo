//
//  MemoryDemo.m
//  TestOC
//
//  Created by package on 2024/3/26.
//

#import "MemoryDemo.h"
@interface MemoryDemo()
@property (nonatomic, assign) uint8_t* ptr;
@property (nonatomic, assign) int bufferSize;
@end

@implementation MemoryDemo

- (instancetype)init
{
    self = [super init];
    if (self) {
        _bufferSize = 1024*1024*200; // 200MB
        _ptr = malloc(_bufferSize);
        memset(_ptr, 1, _bufferSize);
    }
    return self;
}

-(void) logBuffer {
    for (int i = 0; i < _bufferSize; i += 1000) {
        NSLog(@" %d -- %d", _ptr[i], i);
    }
}

- (void)dealloc {
//    free(_ptr);
    NSLog(@"MemoryDemo dealloc");
}


+(void) run {
    MemoryDemo* demo = [MemoryDemo new];
    [demo logBuffer];
}
@end

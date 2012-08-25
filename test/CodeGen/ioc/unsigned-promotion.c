// Check -fioc-signed on promoted unsigned types
//
// RUN: %clang_cc1 -triple x86_64-apple-darwin10 -emit-llvm -o - %s \
// RUN:   -fioc-signed | FileCheck %s --check-prefix=CHECKS

unsigned short si, sj, sk;
unsigned char ci, cj, ck;

extern void opaqueshort(unsigned short);
extern void opaquechar(unsigned char);

// CHECKS:   define void @testshortadd()
void testshortadd() {
  // CHECKS:        load i16* @sj
  // CHECKS:        load i16* @sk
  // CHECKS:        [[T1:%.*]] = call { i32, i1 } @llvm.sadd.with.overflow.i32(i32 [[T2:%.*]], i32 [[T3:%.*]])
  // CHECKS-NEXT:   [[T4:%.*]] = extractvalue { i32, i1 } [[T1]], 0
  // CHECKS-NEXT:   [[T5:%.*]] = extractvalue { i32, i1 } [[T1]], 1
  // CHECKS:        call void @__ioc_report_add_overflow
  //

  si = sj + sk;
}

// CHECKS:   define void @testshortsub()
void testshortsub() {

  // CHECKS:        load i16* @sj
  // CHECKS:        load i16* @sk
  // CHECKS:        [[T1:%.*]] = call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 [[T2:%.*]], i32 [[T3:%.*]])
  // CHECKS-NEXT:   [[T4:%.*]] = extractvalue { i32, i1 } [[T1]], 0
  // CHECKS-NEXT:   [[T5:%.*]] = extractvalue { i32, i1 } [[T1]], 1
  // CHECKS:        call void @__ioc_report_sub_overflow
  //

  si = sj - sk;
}

// CHECKS:   define void @testshortmul()
void testshortmul() {

  // CHECKS:        load i16* @sj
  // CHECKS:        load i16* @sk
  // CHECKS:        [[T1:%.*]] = call { i32, i1 } @llvm.smul.with.overflow.i32(i32 [[T2:%.*]], i32 [[T3:%.*]])
  // CHECKS-NEXT:   [[T4:%.*]] = extractvalue { i32, i1 } [[T1]], 0
  // CHECKS-NEXT:   [[T5:%.*]] = extractvalue { i32, i1 } [[T1]], 1
  // CHECKS:        call void @__ioc_report_mul_overflow
  //

  si = sj * sk;
}

// CHECKS:   define void @testcharadd()
void testcharadd() {

  // CHECKS:        load i8* @cj
  // CHECKS:        load i8* @ck
  // CHECKS:        [[T1:%.*]] = call { i32, i1 } @llvm.sadd.with.overflow.i32(i32 [[T2:%.*]], i32 [[T3:%.*]])
  // CHECKS-NEXT:   [[T4:%.*]] = extractvalue { i32, i1 } [[T1]], 0
  // CHECKS-NEXT:   [[T5:%.*]] = extractvalue { i32, i1 } [[T1]], 1
  // CHECKS:        call void @__ioc_report_add_overflow
  //

  ci = cj + ck;
}

// CHECKS:   define void @testcharsub()
void testcharsub() {

  // CHECKS:        load i8* @cj
  // CHECKS:        load i8* @ck
  // CHECKS:        [[T1:%.*]] = call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 [[T2:%.*]], i32 [[T3:%.*]])
  // CHECKS-NEXT:   [[T4:%.*]] = extractvalue { i32, i1 } [[T1]], 0
  // CHECKS-NEXT:   [[T5:%.*]] = extractvalue { i32, i1 } [[T1]], 1
  // CHECKS:        call void @__ioc_report_sub_overflow
  //

  ci = cj - ck;
}

// CHECKS:   define void @testcharmul()
void testcharmul() {

  // CHECKS:        load i8* @cj
  // CHECKS:        load i8* @ck
  // CHECKS:        [[T1:%.*]] = call { i32, i1 } @llvm.smul.with.overflow.i32(i32 [[T2:%.*]], i32 [[T3:%.*]])
  // CHECKS-NEXT:   [[T4:%.*]] = extractvalue { i32, i1 } [[T1]], 0
  // CHECKS-NEXT:   [[T5:%.*]] = extractvalue { i32, i1 } [[T1]], 1
  // CHECKS:        call void @__ioc_report_mul_overflow
  //

  ci = cj * ck;
}

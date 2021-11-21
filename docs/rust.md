# Rust how to

## FFI

Rust FFI Omnibus is a good site that contains many examples from the web

http://jakegoulding.com/rust-ffi-omnibus/

## Return data on the heap

https://stackoverflow.com/questions/57616229/returning-array-from-rust-to-ffi

For an array, we could use:

- A vec and explicitly tell Rust not to deallocate it
	```rust
	#[no_mangle]
	pub extern "C" fn ffi_test() -> *mut u16 {
		let mut test = vec![1, 2, 3, 4];
		let ptr = test.as_mut_ptr();
		
		std::mem::forget(test); // so that it is not destructed at the end of the scope
		
		ptr
	}
	```

- A Box, and return a raw pointer (don't forget to cast)
	```rust
	#[no_mangle]
	pub extern "C" fn ffi_test() -> *mut u16 {
		let test = Box::new([1u16, 2, 3, 4]);  // type must be explicit here...

		Box::into_raw(test) as *mut _	// ... because this cast can convert
										// *mut [i32; 4] to *mut u16
	}
	```
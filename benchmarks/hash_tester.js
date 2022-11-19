const fs = require("fs");

const path = process.env.PATH;
const bins = path.split(":").flatMap((p) => fs.readdirSync(p));
const bestConfig = {
	arrSize: +Infinity,
	duplicates: +Infinity,
};

const test_hash_params = (arrSize, hasher) => {
	const set = new Set();

	for (const bin of bins) {
		set.add(hasher(bin, arrSize));
	}

	const dupls = bins.length - set.size;
	if (dupls < bestConfig.duplicates) {
		bestConfig.arrSize = arrSize;
		bestConfig.duplicates = dupls;
	}
};

const hash = (str, size) => {
	let i = 0;
	for (let j = 0; str[j]; j++) {
		i += str.charCodeAt(j) * ((i ^ str.charCodeAt(j)) + j);
	}
	return i % size;
};

// BEST: { arrSize: 4031, duplicates: 99 }
// i += str.charCodeAt(j) * ((i ^ str.charCodeAt(j)) + str.length);

// ALT. WITHOUT STRLEN: { arrSize: 3939, duplicates: 100 }
// i += str.charCodeAt(j) * ((i ^ str.charCodeAt(j)) + j);
for (let size = 2048; size <= 4096; size++) {
	test_hash_params(size, hash);
}

console.log(bestConfig);

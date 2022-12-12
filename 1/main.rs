use std::io;
use std::cmp;
use std::io::BufRead;

fn main() {
    let mut curr = 0;
    let mut ans = 0;

    for line in io::stdin().lock().lines() {
        let s = line.unwrap();
        if s.is_empty() {
            ans = cmp::max(ans, curr);
            curr = 0;
        } else {
            let n: u32 = s.trim().parse().expect("fuck");
            curr += n;
        }
    }

    println!("{}", ans);
}

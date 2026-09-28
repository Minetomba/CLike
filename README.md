## About the project
This is a compiler for a typeless programming language with syntax combining the best features from Lua, C, and B.
Any stable release must accurately run and compile the syntax.
Snapshots may be released before the first stable release or between stable releases.
Stable versions are tested thoroughly before released.
## Contributing
### Code structure
#### Newlines
Newlines shall be appended after each character within the defined list of characters "{};" or at the character closing the name of what to include at a line that starts with #include. Newlines can be added after the closure of an area of code. Exceptions include:
- Comments (May be added wherever meaning is clearer).
- "for" loop headers.
- "else" after a closing bracket shall not have a newline but instead have a space character.
#### Indentation
Indentation starts as 0 by default, and on each line N tabs prefix the following code where N is the indentation level.
Indentation level is incremented by the occurence of the character '{' and decremented by the the occurence of the character '}'.
Indentation is only done with tabs.
#### Spacing
Spacing is added before and after every operator that may arithmetically or logically modify/output a number/variable/memory slot from an input number/variable/memory slot. Unary operators are exempt and should only have spacing before them but not after the operator. Attributions like "foo.x", "foo[x]" or "foo->x" are exempt and must not have spacing.
#### Includes
All includes are at the top, right below the license/copyright message.
#### Comments
Comments are added where the code doesn't explain what it does. Comments are exempt from all newline/indentation rules and shall be added at a position wherever clearer.
Comments are used at the beggining of a code block to name that area.
### Building
At the root of this repository:
```bash
./compile.sh
```
### Commit messages
Last commit message's integer value incremented where the first commit message is "1", the second one is "2", and so on. The changes themselves via "git diff" are the "What changed?" part of a commit rather than the commit message.
Commit messages, beside the integer value, will contain "-" followed by "snapshot" or "stable" depending on whether it's a stable release or just a snapshot.
### Other notes
- Patches can be sent through GitHub as a pull request.
### Security Vulnerabilities
Report at <minetomba@proton.me>, expect a response or patch within 7 days.
Options for reporting:
- Report with no other data other than the vulnerability, but you will get no credit.
- Report with something like your github username and/or an email you reply through, and you will receive credit.
Information needed for submission:
- If the vulnerability was identified through dynamic analysis, a PoC and the type of the vulnerability will need to be submitted.
- If the vulnerability was identified through static analysis, the specific affected lines and/or the area of code affected and the type of vulnerability will need to be submitted.
## License
GPL-3.0-only. See [LICENSE](LICENSE).
Copyright (C) 2026 minetomba <minetomba@proton.me>.
If you fork or reuse this, keep this notice and the license intact.
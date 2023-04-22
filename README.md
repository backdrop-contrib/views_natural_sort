# Views Natural Sort

Provides a views filter that sorts node titles by a more natural manner by ignoring articles like "A" "An" and "The."

Normal sort:

A Chorus Line
* All American
* Fiddler on the Roof
* Oklahoma!
* The King And I
* Natural sort:

All American
* A Chorus Line
* Fiddler on the Roof
* The King And I
* Oklahoma!
* Natural Sort also supports Numbers.

Normal Sort:

* 1 apple
* 10 apples
* 2 apples

Natural Sort:
* 1 apple
* 2 apples
* 10 apples

This is done using a prebuilt, indexed table so it should perform well.

## Installation

- Install this module using the official
  [Backdrop CMS instructions](https://backdropcms.org/user-guide/modules).

## Issues

Bugs and feature requests should be reported in the
[Issue Queue](https://github.com/backdrop-contrib/views_natural_sort/issues).

## Current Maintainers

[Justin Keiser](https://github.com/keiserjb)<br>
[Allan Chappell](https://github.com/generalredneck)

## Credits

- Ported to Backdrop CMS by [Justin Keiser](https://github.com/keiserjb).
- Many thanks to the creators of the [Drupal project](https://www.drupal.org/project/views_natural_sort).

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

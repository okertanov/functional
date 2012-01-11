Github API
==========

General
-------
* ``http://github.com/api/v2/:format`` (json, xml, yaml)
* API limited to 60 calls per minute
* ``?callback=myCbFunction`` - it will wrap the result JSON in that function, so you can automatically execute it.
* ``curl -u "okertanov:PASSWORD" https://github.com/api/v2/json/user/show/okertanov``

Git
---

Gists (an old API)
------------------
* List: ``curl https://gist.github.com/api/v1/json/gists/okertanov``
* Metadata: ``curl https://gist.github.com/api/v1/json/855376``
* Content: ``curl https://gist.github.com/raw/855376/"useful-unix-commands.md"``
* New: ``http://gist.github.com/api/v1/json/new``

Gists (a new API)
------------------
* User info: ``curl -i https://api.github.com/users/okertanov``
* Gists list: ``curl -i https://api.github.com/users/okertanov/gists``
* Get the gist: ``curl -i https://api.github.com/gists/847623``
* Create a new gist: ``POST /users/okertanov/gists``
    {
        "description" => "the description for this gist",
        "public" => true,
        "files"  =>
            {
                "file1.txt"=>{"content"=>"String file contents"}
            }
    }
* Edit a gist: ``PATCH /gists/:id``
    {
        "description"=>"the description for this gist",
        "files" =>
        {
            "file1.txt" => {"content"=>"String file contents"}
        }
    }
* Check if a gist is starred: ``GET /gists/:id/star``
* Star a gist:   ``POST /gists/:id/star``
* Unstar a gist: ``DELETE /gists/:id/star``
* Fork a gist:   ``POST /gists/:id/fork``
* Delete a gist: ``DELETE /gists/:id``

Links
-----
1. [Develop.Github API v2][1]
2. [Develop.Github API v3][2]
3. [Develop.Github:Gists API v3][3]
4. [gist.rb with urls][4]

[1]: http://develop.github.com/
[2]: http://developer.github.com/v3/
[3]: http://developer.github.com/v3/gists/
[4]: https://gist.github.com/288279
